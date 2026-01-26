#include "client/core/grpc_client_base.hpp"

void GrpcClientBase::attachAuth(grpc::ClientContext &ctx) {
    const auto token = TokenManager::instance().accessToken();
    if (!token.empty()) {
        ctx.AddMetadata("authorization", "Bearer " + token);
    }
}

bool GrpcClientBase::tryRefresh(AuthClient &auth) {
    auto &tm = TokenManager::instance();

    const std::string refresh = tm.refreshToken();
    if (refresh.empty())
        return false;

    AuthClient::AuthTokens tokens;
    AuthClient::AuthResult res = auth.refreshToken(tm.accessToken(), refresh, tokens);

    if (res != AuthClient::SUCCESS)
        return false;

    tm.setAccessToken(tokens.access_token);
    tm.setRefreshToken(tokens.refresh_token);
    
    return true;
}