#include "database/dao/postgres/pg_gladiator_dao.hpp"

#include "database/dao/errors.hpp"
#include "utils/db_config.hpp"

std::optional<db::Gladiator> PgGladiatorDao::getByOwnerId(const std::string &owner_id) {
    try {
        pqxx::connection conn{utils::getDbConnectionString()};
        pqxx::work tx{conn};

        auto result = tx.exec_params(
            "SELECT * FROM gladiators WHERE owner_id = $1 LIMIT 1",
            owner_id
        );

        tx.commit();

        if (result.empty())
            return std::nullopt;

        return rowToGladiator(result[0]);
    }
    catch (const std::exception& e) {
        throw db::DaoError(e.what());
    }
}

void PgGladiatorDao::updateStatByValue(const std::string &gladiator_id, Stats stat, std::uint64_t value) {
    try {
        pqxx::connection conn{utils::getDbConnectionString()};
        pqxx::work tx{conn};

        std::string query;

        switch (stat) {
            case 0:
                query =
                    "UPDATE gladiators "
                    "SET strength = strength + $1 "
                    "WHERE gladiator_id = $2";
                break;

            case 1:
                query =
                    "UPDATE gladiators "
                    "SET dexterity = dexterity + $1 "
                    "WHERE gladiator_id = $2";
                break;

            case 2:
                query =
                    "UPDATE gladiators "
                    "SET defence = defence + $1 "
                    "WHERE gladiator_id = $2";
                break;

            case 3:
                query =
                    "UPDATE gladiators "
                    "SET vitality = vitality + $1 "
                    "WHERE gladiator_id = $2";
                break;

            default:
                throw std::invalid_argument("Invalid stat");
        }

        tx.exec_params(query, value, gladiator_id);

        tx.commit();
    }
    catch (const std::exception& e) {
        throw db::DaoError(e.what());
    }
}
