#include "client/frontend/models/gladiator_qml.hpp"

GladiatorQML::GladiatorQML(QObject *parent) : QObject(parent) {}

QString GladiatorQML::id() const {
    return this->id_; 
}

QString GladiatorQML::name() const {
    return this->name_; 
}

QString GladiatorQML::gladiatorClass() const {
    return this->gladiatorClass_;
}

quint64 GladiatorQML::strength() const {
    return this->strength_;
}

quint64 GladiatorQML::dexterity() const {
    return this->dexterity_;
}

quint64 GladiatorQML::defence() const {
    return this->defence_;
}

quint64 GladiatorQML::vitality() const { 
    return this->vitality_;
}

void GladiatorQML::populate(const QString &id, const QString &name, const QString &gladiatorClass, quint64 strength, quint64 dexterity, quint64 defence, quint64 vitality) {
    this->id_ = id;
    this->name_ = name;
    this->gladiatorClass_ = gladiatorClass;
    this->strength_ = strength;
    this->dexterity_ = dexterity;
    this->defence_ = defence;
    this->vitality_ = vitality;

    emit changed();
}

void GladiatorQML::clear() {
    this->populate("", "", "", 0, 0, 0, 0);
}