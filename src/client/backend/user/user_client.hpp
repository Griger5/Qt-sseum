#pragma once

#include <memory>
#include <grpcpp/grpcpp.h>

#include "proto/user.grpc.pb.h"
#include "client/core/grpc_client_base.hpp"

class UserClient final : public GrpcClientBase {
public:
    struct Profile {
        std::string user_id;
        std::string username;
        std::uint64_t level;
        std::uint64_t experience;
        std::uint64_t money;

        std::string gladiator_id;
        std::string gladiator_name;
        std::string gladiator_class;
        std::uint64_t strength;
        std::uint64_t dexterity;
        std::uint64_t defence;
        std::uint64_t vitality;

        bool item_exists;
        std::string item_id;
        std::string item_name;
        std::uint64_t min;
        std::uint64_t max;
        std::uint64_t item_strength;
        std::uint64_t item_dexterity;
        std::uint64_t item_defence;
        std::uint64_t item_vitality;
    };

    explicit UserClient(std::shared_ptr<grpc::Channel> channel);

    GrpcCallResult getProfile(Profile &profile);

private:
    std::unique_ptr<user::UserService::Stub> stub_;
};