#include "client/backend/arena/arena_client.hpp"

ArenaClient::ArenaClient(std::shared_ptr<grpc::Channel> channel) : GrpcClientBase(channel), stub_(arena::Arena::NewStub(channel)) {}

GrpcCallResult ArenaClient::getOpponents(std::uint32_t number_of_ops, std::vector<Opponent> &opponents) {
    grpc::ClientContext ctx;
    arena::OpponentsRequest request;
    arena::OpponentsResponse response;

    request.set_number_of_ops(number_of_ops);

    return executeWithAuthRetry([&] {
        this->attachAuth(ctx);

        grpc::Status status = this->stub_->getOpponents(&ctx, request, &response);

        for (const auto &opponent : response.opponent()) {
            Opponent next_opponent;

            auto u = opponent.user();
            auto g = opponent.gladiator();
            auto it = opponent.item();

            next_opponent.id = u.id();
            next_opponent.username = u.username();
            next_opponent.level = u.level();
            next_opponent.gladiator_name = g.name();
            next_opponent.gladiator_class = g.gladiator_class();
            next_opponent.item_name = it.name();
            next_opponent.min = it.min();
            next_opponent.max = it.max();
            next_opponent.strength = g.strength() + it.strength();
            next_opponent.dexterity = g.dexterity() + it.dexterity();
            next_opponent.defence = g.defence() + it.defence();
            next_opponent.vitality = g.vitality() + it.vitality();

            opponents.push_back(next_opponent);
        }

        return status;
    });
}