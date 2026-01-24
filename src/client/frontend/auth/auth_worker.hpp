#pragma once

#include <memory>

#include <QObject>
#include <QString>

#include "client/backend/auth/auth_client.hpp"

class AuthWorker : public QObject {
    Q_OBJECT  
public:
    explicit AuthWorker(QObject *parent = nullptr);

public slots:
    void issueToken(const QString &email, const QString &password);
    void refreshToken(const QString &access_token, const QString &refresh_token);

signals:
    void tokensIssued(const QString &access_token, const QString &refresh_token, const quint64 &expires_in);
    void tokensRefreshed(const QString &access_token, const QString &refresh_token, const quint64 &expires_in);
    void invalidCredentials();
    void tokenExpired();
    void authUnavailable();
    void errorOccurred(const QString &error);

private:
    std::unique_ptr<AuthClient> client_;
};