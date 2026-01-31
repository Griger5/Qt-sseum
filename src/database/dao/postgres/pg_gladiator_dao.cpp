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
