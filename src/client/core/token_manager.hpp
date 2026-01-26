#pragma once

#include <string>

#include <QMutex>

class TokenManager final
{
public:
    static TokenManager &instance();

    void setAccessToken(const std::string &token);
    std::string accessToken() const;

    void setRefreshToken(const std::string &token);
    std::string refreshToken() const;

    void loadRefreshToken();
    void clear();

private:
    TokenManager() = default;
    ~TokenManager() = default;

    TokenManager(const TokenManager &) = delete;
    TokenManager& operator=(const TokenManager &) = delete;

    void saveRefreshTokenLocked();
    void loadRefreshTokenLocked();
    void clearLocked();

private:
    mutable QMutex mutex_;
    std::string access_token_;
    std::string refresh_token_;
};
