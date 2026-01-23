#pragma once

namespace db {

struct User {
    std::string id;
    std::string username;
    std::string email;
    std::string password_hash;
};

inline User rowToUser(const pqxx::row &r) {
    return User{
        r["id"].as<std::string>(),
        r["username"].as<std::string>(),
        r["email"].as<std::string>(),
        r["password_hash"].as<std::string>()
    };
}

} // db