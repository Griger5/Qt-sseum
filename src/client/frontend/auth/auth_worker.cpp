#include "client/frontend/auth/auth_worker.hpp"

#include <exception>

#include <grpcpp/grpcpp.h>


AuthWorker::AuthWorker(QObject *parent) : QObject(parent), client_(std::make_unique<AuthClient>(grpc::CreateChannel("server:50051", grpc::InsecureChannelCredentials()))) {}

void AuthWorker::issueToken(const QString &email, const QString &password) {
    try {
        AuthClient::AuthTokens tokens;
        AuthClient::AuthResult reply = this->client_->issueToken(email.toStdString(), password.toStdString(), tokens);

        switch (reply) {
            case AuthClient::SUCCESS:
                emit tokensIssued(QString::fromStdString(tokens.access_token), QString::fromStdString(tokens.refresh_token), tokens.expires_in);
                break;
            case AuthClient::INVALID_CREDENTIALS:
                emit invalidCredentials();
                break;
            case AuthClient::UNAVAILABLE:
                emit authUnavailable();
                break;
            case AuthClient::INTERNAL_ERROR:
                emit errorOccurred("Internal server error");
                break;
        }
    }
    catch (const std::exception &e) {
        emit errorOccurred(QString::fromStdString(e.what()));
    }
}

void AuthWorker::refreshToken(const QString &access_token, const QString &refresh_token) {
    try {
        AuthClient::AuthTokens tokens;
        AuthClient::AuthResult reply = this->client_->refreshToken(access_token.toStdString(), refresh_token.toStdString(), tokens);

        switch (reply) {
            case AuthClient::SUCCESS:
                emit tokensIssued(QString::fromStdString(tokens.access_token), QString::fromStdString(tokens.refresh_token), tokens.expires_in);
                break;
            case AuthClient::TOKEN_EXPIRED:
                emit tokenExpired();
                break;
            case AuthClient::INVALID_CREDENTIALS:
                emit invalidCredentials();
                break;
            case AuthClient::INTERNAL_ERROR:
                emit errorOccurred("Internal server error");
                break;
        }
    }
    catch (const std::exception &e) {
        emit errorOccurred(QString::fromStdString(e.what()));
    }
}