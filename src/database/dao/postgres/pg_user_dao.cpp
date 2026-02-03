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

std::optional<db::UserAuth> PgUserDao::getUserForAuth(const std::string &email) {
    try {
        pqxx::connection conn{utils::getDbConnectionString()};

        pqxx::work tx{conn};

        auto result = tx.exec_params(
            "SELECT id, password_hash, role FROM users WHERE email = $1 LIMIT 1",
            email
        );

        tx.commit();

        if (result.empty()) {
            return std::nullopt;
        }

        const pqxx::row r = result[0];

        return PgUserDao::rowToUserAuth(r);
    }
    catch (const std::exception &e) {
        throw db::DaoError(e.what());
    }
}

std::optional<db::UserStats> PgUserDao::getUserStats(const std::string &id) {
    try {
        pqxx::connection conn{utils::getDbConnectionString()};

        pqxx::work tx{conn};

        auto result = tx.exec_params(
            "SELECT u.id, u.username, ps.money, ps.level, ps.exp FROM users u "
            "JOIN player_stats ps ON u.id = ps.id "
            "WHERE u.id = $1 LIMIT 1",
            id
        );

        tx.commit();

        if (result.empty()) {
            return std::nullopt;
        }

        const pqxx::row r = result[0];

        return PgUserDao::rowToUserStats(r);
    }
    catch (const std::exception &e) {
        throw db::DaoError(e.what());
    }
}

std::optional<std::vector<db::UserStats>> PgUserDao::getRandomUserStats(std::uint32_t number_of_users, const std::string &id_to_skip) {
    try {
        pqxx::connection conn{utils::getDbConnectionString()};

        pqxx::work tx{conn};

        auto result = tx.exec_params(
            "SELECT u.id, u.username, ps.money, ps.level, ps.exp FROM users u "
            "JOIN player_stats ps ON u.id = ps.id "
            "WHERE u.id != $1 "
            "ORDER BY random() LIMIT $2",
            id_to_skip, number_of_users
        );

        tx.commit();

        if (result.empty()) {
            return std::nullopt;
        }

        std::vector<db::UserStats> user_stats;

        for (const pqxx::row &r : result) {
            user_stats.push_back(PgUserDao::rowToUserStats(r));
        }

        if (user_stats.size() < number_of_users) {
            return std::nullopt;
        }

        return user_stats;
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

std::int64_t PgUserDao::addUserMoney(const std::string &id, std::int64_t value) {
    try {
        pqxx::connection conn{utils::getDbConnectionString()};
        pqxx::work tx{conn};

        auto result = tx.exec_params(
            "UPDATE player_stats "
            "SET money = money + $1 "
            "WHERE id = $2 "
            "RETURNING money", 
            value, id
        );

        if (result.empty()) {
            throw db::DaoError("User not found");
        }

        tx.commit();

        return result[0][0].as<std::int64_t>();
    }
    catch (const std::exception& e) {
        throw db::DaoError(e.what());
    }
}