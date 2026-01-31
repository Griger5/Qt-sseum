#pragma once

#include <string>
#include <optional>

#include "database/model/gladiator.hpp"

class IGladiatorDao {
public:
    virtual ~IGladiatorDao() = default;

    virtual std::optional<db::Gladiator> getByOwnerId(const std::string &owner_id) = 0;
};