#pragma once

#include <string>
#include <memory>

#include <grpcpp/grpcpp.h>

#include "proto/arena.grpc.pb.h"

#include "client/core/grpc_client_base.hpp"

class ArenaClient : public GrpcClientBase {
public:
    struct Opponent {
        std::string id;
        std::string username;
        std::uint64_t level;
        std::string gladiator_name;
        std::string gladiator_class;
        std::string item_name;
        std::uint64_t min;
        std::uint64_t max;
        std::uint64_t strength;
        std::uint64_t dexterity;
        std::uint64_t defence;
        std::uint64_t vitality;
    };

    ArenaClient(std::shared_ptr<grpc::Channel> channel);

    GrpcCallResult getOpponents(std::uint32_t number_of_ops, std::vector<Opponent> &opponents);

private:
    std::unique_ptr<arena::Arena::Stub> stub_;
};