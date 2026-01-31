#pragma once

#include <string>
#include <optional>

#include "database/model/item.hpp"

class IItemDao {
public:
    virtual ~IItemDao() = default;

    virtual std::optional<db::Item> getItemById(const std::string &item_id) = 0;
};