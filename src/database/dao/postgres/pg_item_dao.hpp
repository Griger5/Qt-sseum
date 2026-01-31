#pragma once

#include <string>
#include <optional>

#include <pqxx/pqxx>

#include "database/dao/i_item_dao.hpp"

class PgItemDao final : public IItemDao {
public:
    std::optional<db::Item> getItemById(const std::string &item_id) override;

private:
    static db::Item rowToItem(const pqxx::row &r) {
        return db::Item{
            r["item_id"].as<std::string>(),
            r["name"].as<std::string>(),
            r["min"].as<std::uint64_t>(),
            r["max"].as<std::uint64_t>(),
            r["strength"].as<std::uint64_t>(),
            r["dexterity"].as<std::uint64_t>(),
            r["defence"].as<std::uint64_t>(),
            r["vitality"].as<std::uint64_t>()
        };
    }
};