#pragma once

#include <string>
#include <optional>

#include <pqxx/pqxx>

#include "database/dao/i_user_dao.hpp"

class PgUserDao final : public IUserDao {
public:
    explicit PgUserDao(pqxx::connection &conn);

    bool userExists(const std::string &email) override;
    std::optional<db::User> getUserById(const std::string &id) override;
    std::optional<db::User> getUserByEmail(const std::string &email) override;
    void createUser(const std::string &username, const std::string &email, const std::string &password_hash) override;

private:
    pqxx::connection &conn_;
};