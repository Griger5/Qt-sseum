#include "client/core/session_logic.hpp"

SessionLogic::SessionLogic(UserQML *user, GladiatorQML *gladiator, ItemQML *item, QObject *parent) : QObject(parent), user(user), gladiator(gladiator), item(item) {
    connect(&userClient, &UserClientQt::profileLoaded, this, &SessionLogic::onProfileLoaded);
    connect(&userClient, &UserClientQt::errorOccurred, this, &SessionLogic::errorOccurred);
}

void SessionLogic::onLoginSuccessful() {
    this->userClient.loadProfileAsync();
}

void SessionLogic::onProfileLoaded(const UserClient::Profile &profile) {
    user->populate(QString::fromStdString(profile.user_id), QString::fromStdString(profile.username), profile.level, profile.experience, profile.money);

    gladiator->populate(QString::fromStdString(profile.gladiator_id), QString::fromStdString(profile.gladiator_name), QString::fromStdString(profile.gladiator_class), profile.strength, profile.dexterity, profile.defence, profile.vitality);

    item->populate(QString::fromStdString(profile.item_id), QString::fromStdString(profile.item_name), profile.min, profile.max, profile.item_strength, profile.item_dexterity, profile.item_defence, profile.item_vitality);

    emit profileReady();
}