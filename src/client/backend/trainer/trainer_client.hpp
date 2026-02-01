#pragma once

#include <string>
#include <memory>

#include <grpcpp/grpcpp.h>

#include "proto/trainer.grpc.pb.h"

#include "client/core/grpc_client_base.hpp"

class TrainerClient : public GrpcClientBase {
public:
    enum Stats {
        STRENGTH = 0,
        DEXTERITY = 1,
        DEFENCE = 2,
        VITALITY = 3
    };

    struct StatUpgradeResult {
        std::uint64_t strength;
        std::uint64_t dexterity;
        std::uint64_t defence;
        std::uint64_t vitality;
        std::uint64_t money;
    };

    TrainerClient(std::shared_ptr<grpc::Channel> channel);

    GrpcCallResult upgradeStat(const std::string &gladiator_id, Stats stat, std::uint64_t value, StatUpgradeResult &result);

private:
    std::unique_ptr<trainer::Trainer::Stub> stub_;
};