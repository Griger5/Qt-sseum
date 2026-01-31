#pragma once

#include <string>

namespace db {

struct Gladiator {
    std::string id;
    std::string owner_id;
    std::string name;
    std::string gladiator_class;
    std::uint64_t strength;
    std::uint64_t dexterity;
    std::uint64_t defence;
    std::uint64_t vitality;
    std::string item_id;
};

} // db