#pragma once

#include <grpcpp/grpcpp.h>

#include "proto/auth.grpc.pb.h"

#include "database/dao/i_user_dao.hpp"

class AuthService : public auth::Auth::Service {
public:
    explicit AuthService(std::shared_ptr<IUserDao> dao);

    grpc::Status issueToken(grpc::ServerContext *context, const auth::IssueTokenRequest *request, auth::IssueTokenResponse *response);

    grpc::Status refreshToken(grpc::ServerContext *context, const auth::RefreshTokenRequest *request, auth::RefreshTokenResponse *response);

private:
    std::shared_ptr<IUserDao> user_dao;

    std::string createJWT(const std::string &type, const std::string &issuer, const size_t &expire_time, const std::string &subject, const std::string &sign, const std::string &pair_id, std::pair<std::string, std::string> &&payload_claim);
};