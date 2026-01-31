#pragma once

#include <grpcpp/grpcpp.h>

#include "proto/user.grpc.pb.h"

#include "database/dao/i_user_dao.hpp"
#include "database/dao/i_gladiator_dao.hpp"
#include "database/dao/i_item_dao.hpp"

class UserService final : public user::UserService::Service {
public:
    UserService(std::unique_ptr<IUserDao> userDao, std::unique_ptr<IGladiatorDao> gladiatorDao, std::unique_ptr<IItemDao> itemDao);

    grpc::Status getProfile(grpc::ServerContext *context, const user::GetProfileRequest *request, user::GetProfileResponse *response) override;

private:
    std::unique_ptr<IUserDao> userDao_;
    std::unique_ptr<IGladiatorDao> gladiatorDao_;
    std::unique_ptr<IItemDao> itemDao_;
};