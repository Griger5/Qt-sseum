#pragma once

#include <string>
#include <optional>
#include <vector>

#include "database/model/user.hpp"

class IUserDao {
public:
    virtual ~IUserDao() = default;

    virtual bool userExists(const std::string &email) = 0;
    virtual std::optional<db::User> getUserById(const std::string &id) = 0;
    virtual std::optional<db::User> getUserByEmail(const std::string &email) = 0;
    virtual std::optional<db::UserAuth> getUserForAuth(const std::string &email) = 0;
    virtual std::optional<db::UserStats> getUserStats(const std::string &id) = 0;
    virtual std::optional<std::vector<db::UserStats>> getRandomUserStats(std::uint32_t number_of_users, const std::string &id_to_skip = "") = 0;
    virtual void createUser(const std::string &username, const std::string &email, const std::string &password_hash) = 0;
    virtual std::int64_t addUserMoney(const std::string &id, std::int64_t value) = 0;
};