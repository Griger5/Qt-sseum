#pragma once

#include <QObject>
#include <QThread>
#include <QString>

#include "client/frontend/auth/auth_worker.hpp"

class AuthClientQt : public QObject {
    Q_OBJECT
public:
    explicit AuthClientQt(QObject *parent = nullptr);
    ~AuthClientQt();

    Q_INVOKABLE void issueTokenAsync(const QString &email, const QString &password);
    Q_INVOKABLE void refreshTokenAsync(const QString &access_token, const QString &refresh_token);

signals:
    void tokensRequested(const QString &email, const QString &password);
    void refreshRequested(const QString &access_token, const QString &refresh_token);
    void tokensIssued(const QString &access_token, const QString &refresh_token, const quint64 &expires_in);
    void tokensRefreshed(const QString &access_token, const QString &refresh_token, const quint64 &expires_in);
    void invalidCredentials();
    void tokenExpired();
    void authUnavailable();
    void errorOccurred(const QString &error);

private:
    QThread workerThread_;
    AuthWorker *worker_;
};