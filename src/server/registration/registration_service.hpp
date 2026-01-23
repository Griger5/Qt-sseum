#pragma once

#include <grpcpp/grpcpp.h>

#include "proto/registration.grpc.pb.h"

#include "database/dao/i_user_dao.hpp"

class RegistrationService final : public registration::Registration::Service {
private:
    std::shared_ptr<IUserDao> user_dao;

public:
    explicit RegistrationService(std::shared_ptr<IUserDao> dao);

    grpc::Status registerUser(grpc::ServerContext *context, const registration::RegisterRequest *request, registration::RegisterResponse *reply) override;
};