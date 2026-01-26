#include "client/core/token_manager.hpp"

#include <cstdlib>

#include <QSettings>
#include <QCoreApplication>
#include <QMutexLocker>

namespace {

const char *envOrDie(const char *name) {
    const char *v = std::getenv(name);
    if (!v) {
        qFatal("Missing environment variable: %s", name);
    }
    return v;
}

}

TokenManager &TokenManager::instance() {
    static TokenManager instance;
 
    return instance;
}

void TokenManager::setAccessToken(const std::string &token) {
    QMutexLocker locker(&mutex_);
    access_token_ = token;
}

std::string TokenManager::accessToken() const {
    QMutexLocker locker(&mutex_);
    return access_token_;
}

void TokenManager::setRefreshToken(const std::string &token) {
    QMutexLocker locker(&mutex_);
    refresh_token_ = token;
    saveRefreshTokenLocked();
}

std::string TokenManager::refreshToken() const {
    QMutexLocker locker(&mutex_);
    return refresh_token_;
}

void TokenManager::loadRefreshToken() {
    QMutexLocker locker(&mutex_);
    loadRefreshTokenLocked();
}

void TokenManager::clear() {
    QMutexLocker locker(&mutex_);
    clearLocked();
}

void TokenManager::saveRefreshTokenLocked() {
    QSettings settings(
        QSettings::UserScope,
        envOrDie("TOKEN_SETTINGS_ORG"),
        envOrDie("TOKEN_SETTINGS_APP")
    );

    const char *key = envOrDie("TOKEN_REFRESH_KEY");

    if (refresh_token_.empty()) {
        settings.remove(key);
    } else {
        settings.setValue(key, QString::fromStdString(refresh_token_));
    }

    settings.sync();
}

void TokenManager::loadRefreshTokenLocked() {
    QSettings settings(
        QSettings::UserScope,
        envOrDie("TOKEN_SETTINGS_ORG"),
        envOrDie("TOKEN_SETTINGS_APP")
    );

    const char *key = envOrDie("TOKEN_REFRESH_KEY");

    refresh_token_ =
        settings.value(key).toString().toStdString();
}

void TokenManager::clearLocked() {
    access_token_.clear();
    refresh_token_.clear();

    QSettings settings(
        QSettings::UserScope,
        envOrDie("TOKEN_SETTINGS_ORG"),
        envOrDie("TOKEN_SETTINGS_APP")
    );

    settings.remove(envOrDie("TOKEN_REFRESH_KEY"));
    settings.sync();
}