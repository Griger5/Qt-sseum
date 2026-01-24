#include "client/backend/auth/auth_client.hpp"

AuthClient::AuthClient(std::shared_ptr<grpc::Channel> channel) : stub_(auth::Auth::NewStub(channel)) {}

AuthClient::AuthResult AuthClient::issueToken(const std::string &email, const std::string &password, AuthTokens &out_tokens) {
    auth::IssueTokenRequest req;
    auth::IssueTokenResponse res;
    grpc::ClientContext ctx;

    req.set_email(email);
    req.set_password(password);

    grpc::Status status = stub_->issueToken(&ctx, req, &res);

    if (status.ok()) {
        out_tokens.access_token = res.access_token();
        out_tokens.refresh_token = res.refresh_token();
        out_tokens.expires_in = res.expires_in();
        
        return SUCCESS;
    }

    switch (status.error_code()) {
        case grpc::StatusCode::NOT_FOUND:
            return INVALID_CREDENTIALS;
        case grpc::StatusCode::UNAUTHENTICATED:
            return INVALID_CREDENTIALS;
        case grpc::StatusCode::UNAVAILABLE:
            return UNAVAILABLE;
        default:
            return INTERNAL_ERROR;
    }
}

AuthClient::AuthResult AuthClient::refreshToken(const std::string &access_token, const std::string &refresh_token, AuthTokens &out_tokens) {
    auth::RefreshTokenRequest req;
    auth::RefreshTokenResponse res;
    grpc::ClientContext ctx;

    req.set_access_token(access_token);
    req.set_refresh_token(refresh_token);

    grpc::Status status = stub_->refreshToken(&ctx, req, &res);

    if (status.ok()) {
        out_tokens.access_token = res.access_token();
        out_tokens.refresh_token = res.refresh_token();
        out_tokens.expires_in = res.expires_in();
        return SUCCESS;
    }

    switch (status.error_code()) {
        case grpc::StatusCode::UNAUTHENTICATED:
            if (status.error_message() == "Expired refresh token") {
                return TOKEN_EXPIRED;
            }
            return INVALID_CREDENTIALS;
        default:
            return INTERNAL_ERROR;
    }
}