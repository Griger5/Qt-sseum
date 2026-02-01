#pragma once
#include <QObject>

#include "client/frontend/models/user_qml.hpp"
#include "client/frontend/models/gladiator_qml.hpp"
#include "client/frontend/models/item_qml.hpp"
#include "client/frontend/user/user_client_qt.hpp"
#include "client/frontend/trainer/trainer_client_qt.hpp"

class SessionLogic : public QObject {
    Q_OBJECT
public:
    SessionLogic(UserQML *user, GladiatorQML *gladiator, ItemQML *item, QObject *parent = nullptr);

    Q_INVOKABLE void onLoginSuccessful();

private slots:
    void onProfileLoaded(const UserClient::Profile &profile);
    
public slots:
    void onStatUpgraded(const TrainerClient::StatUpgradeResult &result);

signals:
    void profileReady();
    void errorOccurred(const QString &error);

private:
    UserQML *user;
    GladiatorQML *gladiator;
    ItemQML *item;
    UserClientQt userClient;
};
