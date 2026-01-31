#include "server/user/user_service.hpp"

#include "database/dao/errors.hpp"
#include "utils/verify_auth.hpp"

UserService::UserService(std::unique_ptr<IUserDao> userDao, std::unique_ptr<IGladiatorDao> gladiatorDao, std::unique_ptr<IItemDao> itemDao) : userDao_(std::move(userDao)), gladiatorDao_(std::move(gladiatorDao)), itemDao_(std::move(itemDao)) {}

grpc::Status UserService::getProfile(grpc::ServerContext *context, const user::GetProfileRequest *request, user::GetProfileResponse *response) {
    try {
        auto user_id = utils::verifyAuth(context);

        if (!user_id) {
            return grpc::Status(grpc::StatusCode::UNAUTHENTICATED, "Invalid token");
        }

        const std::optional<db::UserStats> user = userDao_->getUserStats(*user_id);
        const std::optional<db::Gladiator> gladiator = gladiatorDao_->getByOwnerId(*user_id);

        if (!user || !gladiator) {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "Profile not found");
        }

        const std::optional<db::Item> item = itemDao_->getItemById(gladiator->item_id);

        auto *u = response->mutable_user();
        u->set_id(user->id);
        u->set_username(user->username);
        u->set_level(user->level);
        u->set_experience(user->exp);
        u->set_money(user->money);

        auto *g = response->mutable_gladiator();
        g->set_id(gladiator->id);
        g->set_name(gladiator->name);
        g->set_gladiator_class(gladiator->gladiator_class);
        g->set_strength(gladiator->strength);
        g->set_dexterity(gladiator->dexterity);
        g->set_defence(gladiator->defence);
        g->set_vitality(gladiator->vitality);

        if (item) {
            auto *i = response->mutable_item();
            i->set_id(item->id);
            i->set_name(item->name);
            i->set_min(item->min);
            i->set_max(item->max);
            i->set_strength(item->strength);
            i->set_dexterity(item->dexterity);
            i->set_defence(item->defence);
            i->set_vitality(item->vitality);
            response->set_item_exists(true);
        }
        else {
            response->set_item_exists(false);
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