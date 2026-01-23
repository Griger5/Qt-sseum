#include "database/dao/postgres/pg_user_dao.hpp"

#include <exception>
#include <optional>

#include "database/dao/errors.hpp"
#include "utils/db_config.hpp"

bool PgUserDao::userExists(const std::string &email) {
    try {
        pqxx::connection conn{utils::getDbConnectionString()};

        pqxx::work tx{conn};

        auto result = tx.exec_params(
            "SELECT 1 FROM users WHERE email = $1 LIMIT 1",
            email
        );

        tx.commit();

        return !result.empty();
    }
    catch (const std::exception &e) {
        throw db::DaoError(e.what());
    }
}

std::optional<db::User> PgUserDao::getUserById(const std::string &id) {
    try {
        pqxx::connection conn{utils::getDbConnectionString()};

        pqxx::work tx{conn};

        auto result = tx.exec_params(
            "SELECT * FROM users WHERE id = $1 LIMIT 1",
            id
        );

        tx.commit();

        if (result.empty()) {
            return std::nullopt;
        }

        const pqxx::row r = result[0];

        return PgUserDao::rowToUser(r);
    }
    catch (const std::exception &e) {
        throw db::DaoError(e.what());
    }
}

std::optional<db::User> PgUserDao::getUserByEmail(const std::string &email) {
    try {
        pqxx::connection conn{utils::getDbConnectionString()};

        pqxx::work tx{conn};

        auto result = tx.exec_params(
            "SELECT * FROM users WHERE email = $1 LIMIT 1",
            email
        );

        tx.commit();

        if (result.empty()) {
            return std::nullopt;
        }

        const pqxx::row r = result[0];

        return PgUserDao::rowToUser(r);
    }
    catch (const std::exception &e) {
        throw db::DaoError(e.what());
    }
}

void PgUserDao::createUser(const std::string &username, const std::string &email, const std::string &password_hash) {
    try {
        pqxx::connection conn{utils::getDbConnectionString()};

        pqxx::work tx{conn};

        auto result = tx.exec_params(
            "INSERT INTO users (username, email, password_hash) VALUES ($1, $2, $3)",
            username, email, password_hash
        );

        tx.commit();
    }
    catch (const pqxx::unique_violation &e) {
        throw db::AlreadyExists("User with this email already exists");
    }
    catch (const std::exception &e) {
        throw db::DaoError(e.what());
    }
}