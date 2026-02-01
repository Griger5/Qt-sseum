#pragma once

#include <string>
#include <optional>

#include <pqxx/pqxx>

#include "database/dao/i_gladiator_dao.hpp"

class PgGladiatorDao final : public IGladiatorDao {
public:
    std::optional<db::Gladiator> getByOwnerId(const std::string& owner_id) override;
    void updateStatByValue(const std::string &gladiator_id, Stats stat, std::uint64_t value) override;

private:
    static db::Gladiator rowToGladiator(const pqxx::row &r) {
        return {
            r["gladiator_id"].as<std::string>(),
            r["owner_id"].as<std::string>(),
            r["name"].as<std::string>(),
            r["class"].as<std::string>(),
            r["strength"].as<std::uint64_t>(),
            r["dexterity"].as<std::uint64_t>(),
            r["defence"].as<std::uint64_t>(),
            r["vitality"].as<std::uint64_t>(),
            r["item_id"].is_null() ? "" : r["item_id"].as<std::string>()
        };
    }
};