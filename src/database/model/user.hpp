#pragma once

namespace db {

struct User {
    std::string id;
    std::string username;
    std::string email;
    std::string password_hash;
    std::string role;
};

struct UserAuth {
    std::string id;
    std::string password_hash;
    std::string role;
};

struct UserStats {
    std::string id;
    std::string username;
    std::uint64_t money;
    std::uint64_t level;
    std::uint64_t exp;
};

} // db