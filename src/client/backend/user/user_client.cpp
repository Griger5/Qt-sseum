#include "client/backend/user/user_client.hpp"

UserClient::UserClient(std::shared_ptr<grpc::Channel> channel) : GrpcClientBase(channel), stub_(user::UserService::NewStub(channel)) {}

GrpcCallResult UserClient::getProfile(UserClient::Profile &profile) {
    grpc::ClientContext ctx;
    user::GetProfileRequest req;
    user::GetProfileResponse res;

    return executeWithAuthRetry([&] {
        this->attachAuth(ctx);

        grpc::Status status = this->stub_->getProfile(&ctx, req, &res);

        if (status.ok()) {
            auto &u = res.user();
            auto &g = res.gladiator();
            auto &i = res.item();

            profile.user_id = u.id();
            profile.username = u.username();
            profile.level = u.level();
            profile.experience = u.experience();
            profile.money = u.money();

            profile.gladiator_id = g.id();
            profile.gladiator_name = g.name();
            profile.gladiator_class = g.gladiator_class();
            profile.strength = g.strength();
            profile.dexterity = g.dexterity();
            profile.defence = g.defence();
            profile.vitality = g.vitality();

            profile.item_exists = res.item_exists();

            if (res.item_exists()) {
                profile.item_id = i.id();
                profile.item_name = i.name();
                profile.min = i.min();
                profile.max = i.max();
                profile.item_strength = i.strength();
                profile.item_dexterity = i.dexterity();
                profile.item_defence = i.defence();
                profile.item_vitality = i.vitality();
            }
        }

        return status;
    });
}