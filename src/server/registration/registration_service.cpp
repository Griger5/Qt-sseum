#include "server/registration/registration_service.hpp"

#include <bcrypt/BCrypt.hpp>

#include "database/dao/errors.hpp"

RegistrationService::RegistrationService(std::unique_ptr<IUserDao> dao) : user_dao(std::move(dao)) {}

grpc::Status RegistrationService::registerUser(grpc::ServerContext *context, const registration::RegisterRequest *request, registration::RegisterResponse *reply) {
    std::string username = request->username();
    std::string email = request->email();
    std::string password = request->password();

    std::string hash = BCrypt::generateHash(password);

    try {
        if (user_dao->userExists(email)) {
            return grpc::Status(grpc::StatusCode::ALREADY_EXISTS, "User already exists");
        }

        user_dao->createUser(username, email, hash);
        reply->set_success(true);

        return grpc::Status::OK;
    }
    catch (const db::AlreadyExists &e) {
        return grpc::Status(grpc::StatusCode::ALREADY_EXISTS, e.what());
    }
    catch (const db::DaoError &e) {
        return grpc::Status(grpc::StatusCode::UNAVAILABLE, e.what());
    }
    catch (const std::exception &e) {
        return grpc::Status(grpc::StatusCode::INTERNAL, e.what());
    }
}