#pragma once

#include <grpcpp/grpcpp.h>

#include "proto/trainer.grpc.pb.h"

#include "database/dao/i_user_dao.hpp"
#include "database/dao/i_gladiator_dao.hpp"

class TrainerService final : public trainer::Trainer::Service {
public:
    TrainerService(std::unique_ptr<IUserDao> user_dao, std::unique_ptr<IGladiatorDao> gladiator_dao);

    grpc::Status upgradeStat(grpc::ServerContext *context, const trainer::UpgradeRequest *request, trainer::UpgradeResponse *reply) override;

private:
    std::unique_ptr<IUserDao> user_dao;
    std::unique_ptr<IGladiatorDao> gladiator_dao;
};