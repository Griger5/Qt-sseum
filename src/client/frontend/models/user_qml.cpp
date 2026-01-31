#include "client/frontend/models/user_qml.hpp"

UserQML::UserQML(QObject *parent) : QObject(parent) {}

QString UserQML::id() const {
    return this->id_;
}

QString UserQML::username() const {
    return this->username_;
}

quint64 UserQML::level() const {
    return this->level_;
}

quint64 UserQML::experience() const {
    return this->experience_; 
}

quint64 UserQML::money() const {
    return this->money_;
}

void UserQML::populate(const QString &id, const QString &username, quint64 level, quint64 experience, quint64 money) {
    this->id_ = id;
    this->username_ = username;
    this->level_ = level;
    this->experience_ = experience;
    this->money_ = money;

    emit changed();
}

void UserQML::clear() {
    populate("", "", 1, 0, 0);
}