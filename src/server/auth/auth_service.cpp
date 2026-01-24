#include "server/auth/auth_service.hpp"

#include <bcrypt/BCrypt.hpp>
#include <jwt-cpp/jwt.h>
#include <uuid_v4.h>

#include "database/dao/errors.hpp"

AuthService::AuthService(std::shared_ptr<IUserDao> dao) : user_dao(dao) {}

std::string AuthService::createJWT(const std::string &type, const std::string &issuer, const size_t &expire_time, const std::string &subject, const std::string &sign, const std::string &pair_id, std::pair<std::string, std::string> &&payload_claim) {
    return jwt::create()
        .set_issued_now()
        .set_type(type)
        .set_issuer(issuer)
        .set_expires_in(std::chrono::seconds{expire_time})
        .set_payload_claim(payload_claim.first, jwt::claim(payload_claim.second))
        .set_payload_claim("pair_id", jwt::claim(pair_id))
        .set_subject(subject)
        .sign(jwt::algorithm::hs256{sign});
}

grpc::Status AuthService::issueToken(grpc::ServerContext *context, const auth::IssueTokenRequest *request, auth::IssueTokenResponse *response) {
    try {
        const std::optional<db::UserAuth> result = this->user_dao->getUserForAuth(request->email());

        if (!result.has_value()) {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "Invalid credentials");
        }

        const db::UserAuth user = result.value();

        if (!BCrypt::validatePassword(request->password(), user.password_hash)) {
            return grpc::Status(grpc::StatusCode::UNAUTHENTICATED, "Invalid credentials");
        }

        UUIDv4::UUIDGenerator<std::mt19937_64> uuid;
        const std::string pair_id = uuid.getUUID().str();

        const size_t access_exp = std::stoll(std::getenv("QTSSEUM_JWT_EXP"));

        std::string token = this->createJWT("JWS", std::getenv("QTSSEUM_JWT_ISSUER"), access_exp, user.id, std::getenv("QTSSEUM_JWT_SECRET"), pair_id, {"role", user.role});

        std::string refresh = this->createJWT("JWS", std::getenv("QTSSEUM_JWT_ISSUER"), std::stoll(std::getenv("QTSSEUM_JWT_REF_EXP")), user.id, std::getenv("QTSSEUM_JWT_SECRET"), pair_id, {"type", "refresh"});

        response->set_access_token(token);
        response->set_refresh_token(refresh);
        response->set_expires_in(access_exp);

        return grpc::Status::OK;
    }
    catch (const db::DaoError &e) {
        return grpc::Status(grpc::StatusCode::UNAVAILABLE, e.what());
    }
    catch (const std::exception& e) {
        return grpc::Status(grpc::StatusCode::INTERNAL, e.what());
    }
}

grpc::Status AuthService::refreshToken(grpc::ServerContext *context, const auth::RefreshTokenRequest *request, auth::RefreshTokenResponse *response) {
    try {
        auto decoded_token = jwt::decode(request->access_token());
        auto decoded_refresh = jwt::decode(request->refresh_token());

        auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{std::getenv("QTSSEUM_JWT_SECRET")})
            .with_issuer(std::getenv("QTSSEUM_JWT_ISSUER"));
            
        std::error_code ec;
        verifier.verify(decoded_refresh, ec);

        switch (ec.value()) {
            case 0:
                break;
            case 14:
                return grpc::Status(grpc::StatusCode::UNAUTHENTICATED, "Expired refresh token");
            default:
                return grpc::Status(grpc::StatusCode::UNAUTHENTICATED, "Invalid refresh token");
        }

        if (decoded_refresh.get_payload_claim("type").as_string() != "refresh") {
            return grpc::Status(grpc::StatusCode::UNAUTHENTICATED, "Not a refresh token");
        }

        if (decoded_token.get_payload_claim("pair_id").as_string() != decoded_refresh.get_payload_claim("pair_id").as_string()) {
            return grpc::Status(grpc::StatusCode::UNAUTHENTICATED, "Token pair mismatch");
        }

        const size_t access_exp = std::stoll(std::getenv("QTSSEUM_JWT_EXP"));

        UUIDv4::UUIDGenerator<std::mt19937_64> uuid;
        const std::string pair_id = uuid.getUUID().str();

        std::string token = this->createJWT("JWS", std::getenv("QTSSEUM_JWT_ISSUER"), access_exp, decoded_refresh.get_subject(), std::getenv("QTSSEUM_JWT_SECRET"), pair_id, {"role", decoded_token.get_payload_claim("role").as_string()});
        
        std::string refresh = this->createJWT("JWS", std::getenv("QTSSEUM_JWT_ISSUER"), std::stoll(std::getenv("QTSSEUM_JWT_REF_EXP")), decoded_refresh.get_subject(), std::getenv("QTSSEUM_JWT_SECRET"), pair_id, {"type", "refresh"});

        response->set_access_token(token);
        response->set_refresh_token(refresh); 
        response->set_expires_in(access_exp);

        return grpc::Status::OK;
    }
    catch (const std::exception &e) {
        return grpc::Status(grpc::StatusCode::INTERNAL, e.what());
    }
}