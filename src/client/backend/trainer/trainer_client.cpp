#include "client/backend/trainer/trainer_client.hpp"

TrainerClient::TrainerClient(std::shared_ptr<grpc::Channel> channel) : GrpcClientBase(channel), stub_(trainer::Trainer::NewStub(channel)) {}

GrpcCallResult TrainerClient::upgradeStat(const std::string &gladiator_id, Stats stat, std::uint64_t value, StatUpgradeResult &result) {
    grpc::ClientContext ctx;
    trainer::UpgradeRequest request;
    trainer::UpgradeResponse response;

    request.set_gladiator_id(gladiator_id);
    request.set_stat(static_cast<trainer::Stats>(stat));
    request.set_value(value);

    return executeWithAuthRetry([&] {
        this->attachAuth(ctx);

        grpc::Status status = this->stub_->upgradeStat(&ctx, request, &response);

        result.strength = response.strength();
        result.dexterity = response.dexterity();
        result.defence = response.defence();
        result.vitality = response.vitality();
        result.money = response.money();

        return status;
    });
}