#pragma once

#include <string>
#include <optional>

#include "database/model/gladiator.hpp"

class IGladiatorDao {
public:
    enum Stats {
        STRENGTH = 0,
        DEXTERITY = 1,
        DEFENCE = 2,
        VITALITY = 3
    };

    virtual ~IGladiatorDao() = default;

    virtual std::optional<db::Gladiator> getByOwnerId(const std::string &owner_id) = 0;
    virtual void updateStatByValue(const std::string &gladiator_id, Stats stat, std::uint64_t value) = 0;
};