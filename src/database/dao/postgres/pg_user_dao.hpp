#pragma once

#include <string>
#include <optional>

#include <pqxx/pqxx>

#include "database/dao/i_user_dao.hpp"

class PgUserDao final : public IUserDao {
public:
    bool userExists(const std::string &email) override;
    std::optional<db::User> getUserById(const std::string &id) override;
    std::optional<db::User> getUserByEmail(const std::string &email) override;
    void createUser(const std::string &username, const std::string &email, const std::string &password_hash) override;

private:
    static db::User rowToUser(const pqxx::row &r) {
        return db::User{
            r["id"].as<std::string>(),
            r["username"].as<std::string>(),
            r["email"].as<std::string>(),
            r["password_hash"].as<std::string>()
        };
    }
};