#pragma once

#include <QObject>
#include <memory>

#include "client/backend/user/user_client.hpp"

class UserWorker : public QObject {
    Q_OBJECT
public:
    explicit UserWorker(QObject *parent = nullptr);

public slots:
    void loadProfile();

signals:
    void profileLoaded(const UserClient::Profile &profile);
    void authExpired();
    void errorOccurred(QString error);

private:
    std::unique_ptr<UserClient> client_;
};