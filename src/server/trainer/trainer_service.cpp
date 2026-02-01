#include "server/trainer/trainer_service.hpp"

#include "database/dao/errors.hpp"
#include "utils/verify_auth.hpp"

TrainerService::TrainerService(std::unique_ptr<IUserDao> user_dao, std::unique_ptr<IGladiatorDao> gladiator_dao) : user_dao(std::move(user_dao)), gladiator_dao(std::move(gladiator_dao)) {}

grpc::Status TrainerService::upgradeStat(grpc::ServerContext *context, const trainer::UpgradeRequest *request, trainer::UpgradeResponse *response) {
    auto user_id = utils::verifyAuth(context);

    if (!user_id) {
        return grpc::Status(grpc::StatusCode::UNAUTHENTICATED, "Invalid token");
    }

    try {
        auto g = this->gladiator_dao->getByOwnerId(*user_id);

        if (!g) {
            return grpc::Status(grpc::StatusCode::PERMISSION_DENIED, "Owner ID of the Gladiator does not match");
        }

        if (request->gladiator_id() != g->id) {
            return grpc::Status(grpc::StatusCode::PERMISSION_DENIED, "Owner ID of the Gladiator does not match");
        }

        this->gladiator_dao->updateStatByValue(request->gladiator_id(), static_cast<IGladiatorDao::Stats>(request->stat()), request->value());
        auto money = this->user_dao->addUserMoney(*user_id, -100);

        response->set_money(money);

        std::uint64_t str = g->strength;
        std::uint64_t dex = g->dexterity;
        std::uint64_t def = g->defence;
        std::uint64_t vit = g->vitality;

        switch (request->stat()){
            case IGladiatorDao::Stats::STRENGTH:
                str += 1;
                break;
            case IGladiatorDao::Stats::DEXTERITY:
                dex += 1;
                break;
            case IGladiatorDao::Stats::DEFENCE:
                def += 1;
                break;
            case IGladiatorDao::Stats::VITALITY:
                vit += 1;
                break;
        }

        response->set_strength(str);
        response->set_dexterity(dex);
        response->set_defence(def);
        response->set_vitality(vit);

        return grpc::Status::OK;
    }
    catch (const db::DaoError &e) {
        return grpc::Status(grpc::StatusCode::UNAVAILABLE, e.what());
    }
    catch (const std::exception &e) {
        return grpc::Status(grpc::StatusCode::INTERNAL, e.what());
    }
}