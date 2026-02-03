#pragma once

#include <grpcpp/grpcpp.h>

#include "proto/arena.grpc.pb.h"

#include "database/dao/i_user_dao.hpp"
#include "database/dao/i_gladiator_dao.hpp"
#include "database/dao/i_item_dao.hpp"

class ArenaService final : public arena::Arena::Service {
public:
    ArenaService(std::unique_ptr<IUserDao> user_dao, std::unique_ptr<IGladiatorDao> gladiator_dao, std::unique_ptr<IItemDao> item_dao);

    grpc::Status getOpponents(grpc::ServerContext *context, const arena::OpponentsRequest *request, arena::OpponentsResponse *response) override;

private:
    std::unique_ptr<IUserDao> user_dao;
    std::unique_ptr<IGladiatorDao> gladiator_dao;
    std::unique_ptr<IItemDao> item_dao;
};