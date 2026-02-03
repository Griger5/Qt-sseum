#include "server/arena/arena_service.hpp"

#include "database/dao/errors.hpp"
#include "utils/verify_auth.hpp"

ArenaService::ArenaService(std::unique_ptr<IUserDao> user_dao, std::unique_ptr<IGladiatorDao> gladiator_dao, std::unique_ptr<IItemDao> item_dao) : user_dao(std::move(user_dao)), gladiator_dao(std::move(gladiator_dao)), item_dao(std::move(item_dao)) {}

grpc::Status ArenaService::getOpponents(grpc::ServerContext *context, const arena::OpponentsRequest *request, arena::OpponentsResponse *response) {
    auto user_id = utils::verifyAuth(context);

    if (!user_id) {
        return grpc::Status(grpc::StatusCode::UNAUTHENTICATED, "Invalid token");
    }

    try {
        auto user_stats_opt = this->user_dao->getRandomUserStats(request->number_of_ops(), *user_id); 

        if (!user_stats_opt) {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "Couldn't find enough users");
        }

        auto user_stats = *user_stats_opt;

        for (std::uint32_t i = 0; i < request->number_of_ops(); ++i) {
            auto *opponent = response->add_opponent();

            auto *user = opponent->mutable_user();
            auto *gladiator = opponent->mutable_gladiator();
            auto *item = opponent->mutable_item();

            auto g = this->gladiator_dao->getByOwnerId(user_stats[i].id);

            if (!g) {
                return grpc::Status(grpc::StatusCode::NOT_FOUND, "Gladiator not found for this user");
            }

            auto it = this->item_dao->getItemById(g->item_id);

            if (!it) {
                return grpc::Status(grpc::StatusCode::NOT_FOUND, "Item not found for this gladiator");
            }

            user->set_id(user_stats[i].id);
            user->set_username(user_stats[i].username);
            user->set_level(user_stats[i].level);
            user->set_experience(user_stats[i].exp);
            user->set_money(user_stats[i].money);

            gladiator->set_id(g->id);
            gladiator->set_name(g->name);
            gladiator->set_gladiator_class(g->gladiator_class);
            gladiator->set_strength(g->strength);
            gladiator->set_dexterity(g->dexterity);
            gladiator->set_defence(g->defence);
            gladiator->set_vitality(g->vitality);

            item->set_id(it->id);
            item->set_name(it->name);
            item->set_min(it->min);
            item->set_max(it->max);
            item->set_strength(it->strength);
            item->set_dexterity(it->dexterity);
            item->set_defence(it->defence);
            item->set_vitality(it->vitality);
        }

        return grpc::Status::OK;
    }
    catch (const db::DaoError &e) {
        return grpc::Status(grpc::StatusCode::UNAVAILABLE, e.what());
    }
    catch (const std::exception &e) {
        return grpc::Status(grpc::StatusCode::INTERNAL, e.what());
    }
}