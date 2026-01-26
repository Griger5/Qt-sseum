#include "utils/verify_jwt.hpp"

#include <cstdlib>
#include <stdexcept>

#include <jwt-cpp/jwt.h>

namespace utils {

bool verifyJWT(const std::string &token) {
    if (token.empty()) {
        return false;
    }

    const std::string issuer = std::getenv("QTSSEUM_JWT_ISSUER");
    const std::string secret = std::getenv("QTSSEUM_JWT_SECRET");

    if (issuer.empty() || secret.empty()) {
        return false;
    }

    try {
        auto decoded = jwt::decode(token);

        if (!decoded.has_expires_at()) {
            return false;
        }

        auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{secret})
            .with_issuer(issuer);

        std::error_code ec;
        verifier.verify(decoded, ec);

        switch (ec.value()) {
            case 0:
                break;
            case 14:
                return false;
            default:
                return false;
        }

        return true;
    }
    catch (const std::exception &) {
        return false;
    }
}

} // utils