#include "database/dao/postgres/pg_item_dao.hpp"

#include <exception>
#include <optional>

#include "database/dao/errors.hpp"
#include "utils/db_config.hpp"

std::optional<db::Item> PgItemDao::getItemById(const std::string &item_id) {
    try {
        if (item_id.empty()) {
            return std::nullopt;
        }

        pqxx::connection conn{utils::getDbConnectionString()};

        pqxx::work tx{conn};

        std::cout << item_id << std::endl;
        auto result = tx.exec_params(
            "SELECT "
            "    ii.item_id, "
            "    (iname.prefix || ' ' || iname.base_name || ' ' || iname.suffix) AS name, "
            "    ii.min_damage AS min, "
            "    ii.max_damage AS max, "
            "    (ip.strength + isf.strength) AS strength, "
            "    (ip.dexterity + isf.dexterity) AS dexterity, "
            "    (ip.defence + isf.defence) AS defence, "
            "    (ip.vitality + isf.vitality) AS vitality "
            "FROM item_instance ii "
            "JOIN item_names iname ON iname.name_id = ii.name_id "
            "JOIN item_prefix ip ON ip.prefix = iname.prefix "
            "JOIN item_suffix isf ON isf.suffix = iname.suffix "
            "WHERE ii.item_id = $1 "
            "LIMIT 1",
            item_id
        );

        tx.commit();

        if (result.empty()) {
            return std::nullopt;
        }

        const pqxx::row r = result[0];

        return PgItemDao::rowToItem(r);
    }
    catch (const std::exception &e) {
        throw db::DaoError(e.what());
    }
}