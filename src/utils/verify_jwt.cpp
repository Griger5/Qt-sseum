#include "utils/verify_jwt.hpp"

#include <cstdlib>
#include <stdexcept>

#include <jwt-cpp/jwt.h>

namespace utils {

std::optional<std::string> verifyJWT(const std::string &token) {
    if (token.empty()) {
        return std::nullopt;
    }

    const std::string issuer = std::getenv("QTSSEUM_JWT_ISSUER");
    const std::string secret = std::getenv("QTSSEUM_JWT_SECRET");

    if (issuer.empty() || secret.empty()) {
        return std::nullopt;
    }

    try {
        auto decoded = jwt::decode(token);

        if (!decoded.has_expires_at()) {
            return std::nullopt;
        }

        auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{secret})
            .with_issuer(issuer);

        std::error_code ec;
        verifier.verify(decoded, ec);

        if (ec.value() != 0)
            return std::nullopt;

        if (!decoded.has_subject())
            return std::nullopt;

        return decoded.get_subject();
    }
    catch (const std::exception &) {
        return std::nullopt;
    }
}

} // utils