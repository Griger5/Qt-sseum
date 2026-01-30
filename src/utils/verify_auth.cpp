#include "utils/verify_auth.hpp"

#include "utils/verify_jwt.hpp"

namespace utils {

std::optional<std::string> verifyAuth(grpc::ServerContext *context) {
    const auto &metadata = context->client_metadata();

    auto it = metadata.find("authorization");
    if (it == metadata.end()) {
        return std::nullopt;
    }

    std::string auth_header(it->second.data(), it->second.length());

    std::string bearer_prefix = "Bearer ";
    if (auth_header.rfind(bearer_prefix, 0) != 0) {
        return std::nullopt;
    }

    std::string token = auth_header.substr(bearer_prefix.length());
    if (token.empty()) {
        return std::nullopt;
    }

    return verifyJWT(token);
}

} // utils