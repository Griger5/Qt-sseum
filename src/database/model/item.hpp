#pragma once

#include <string>

namespace db {

struct Item {
    std::string id;
    std::string name;
    std::uint64_t min;
    std::uint64_t max;
    std::uint64_t strength;
    std::uint64_t dexterity;
    std::uint64_t defence;
    std::uint64_t vitality;
};

} // db