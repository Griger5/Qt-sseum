#include "utils/verify_auth.hpp"

#include "utils/verify_jwt.hpp"

namespace utils {

bool verifyAuth(grpc::ServerContext *context) {
    const auto &metadata = context->client_metadata();

    auto it = metadata.find("authorization");
    if (it == metadata.end()) {
        return false;
    }

    std::string auth_header(it->second.data(), it->second.length());

    std::string bearer_prefix = "Bearer ";
    if (auth_header.rfind(bearer_prefix, 0) != 0) {
        return false;
    }

    std::string token = auth_header.substr(bearer_prefix.length());
    if (token.empty()) {
        return false;
    }

    if (!verifyJWT(token)) {
        return false;
    }

    return true;
}

} // utils