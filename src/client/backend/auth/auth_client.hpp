#pragma once

#include <string>
#include <memory>

#include <grpcpp/grpcpp.h>

#include "proto/auth.grpc.pb.h"

class AuthClient {
public:
    enum AuthResult {
        SUCCESS,
        INVALID_CREDENTIALS,
        TOKEN_EXPIRED,
        UNAVAILABLE,
        INTERNAL_ERROR
    };

    struct AuthTokens {
        std::string access_token;
        std::string refresh_token;
        uint64_t expires_in;
    };

    explicit AuthClient(std::shared_ptr<grpc::Channel> channel);

    AuthResult issueToken(const std::string &email, const std::string &password, AuthTokens &out_tokens);

    AuthResult refreshToken(const std::string &access_token, const std::string &refresh_token, AuthTokens &out_tokens);

private:
    std::unique_ptr<auth::Auth::Stub> stub_;
};