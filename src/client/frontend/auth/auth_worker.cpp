#include "client/frontend/auth/auth_worker.hpp"

#include <exception>

#include "client/core/token_manager.hpp"
#include "client/core/channel_provider.hpp"

AuthWorker::AuthWorker(QObject *parent) : QObject(parent), client_(std::make_unique<AuthClient>(GrpcChannelProvider::instance())) {}

namespace {

void applyTokens(const AuthClient::AuthTokens &tokens) {
    auto& tm = TokenManager::instance();
    tm.setAccessToken(tokens.access_token);
    tm.setRefreshToken(tokens.refresh_token);
}

}

void AuthWorker::issueToken(const QString &email, const QString &password) {
    try {
        AuthClient::AuthTokens tokens;

        auto result = this->client_->issueToken(email.toStdString(), password.toStdString(), tokens);

        if (result == AuthClient::SUCCESS) {
            applyTokens(tokens);
            emit tokensIssued(QString::fromStdString(tokens.access_token), QString::fromStdString(tokens.refresh_token), tokens.expires_in);

            return;
        }

        if (result == AuthClient::INVALID_CREDENTIALS) {
            emit invalidCredentials();
            return;
        }

        if (result == AuthClient::UNAVAILABLE) {
            emit authUnavailable();
            return;
        }

        emit errorOccurred("Internal server error");
    }
    catch (const std::exception& e) {
        emit errorOccurred(e.what());
    }
}

void AuthWorker::refreshToken(const QString &access_token, const QString &refresh_token) {
    try {
        AuthClient::AuthTokens tokens;

        auto result = this->client_->refreshToken(access_token.toStdString(), refresh_token.toStdString(), tokens);

        if (result == AuthClient::SUCCESS) {
            applyTokens(tokens);
            emit tokensIssued(QString::fromStdString(tokens.access_token), QString::fromStdString(tokens.refresh_token), tokens.expires_in);
            return;
        }

        if (result == AuthClient::TOKEN_EXPIRED) {
            emit tokenExpired();
            return;
        }

        if (result == AuthClient::INVALID_CREDENTIALS) {
            emit invalidCredentials();
            return;
        }

        emit errorOccurred("Internal server error");
    }
    catch (const std::exception& e) {
        emit errorOccurred(e.what());
    }
}
