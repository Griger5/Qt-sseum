#include "client/frontend/models/item_qml.hpp"

ItemQML::ItemQML(QObject *parent) : QObject(parent) {}

QString ItemQML::id() const { 
    return this->id_; 
}

QString ItemQML::name() const {
    return this->name_; 
}

quint64 ItemQML::min() const { 
    return this->min_; 
}

quint64 ItemQML::max() const { 
    return this->max_; 
}

quint64 ItemQML::strength() const { 
    return this->strength_; 
}

quint64 ItemQML::dexterity() const { 
    return this->dexterity_; 
}

quint64 ItemQML::defence() const { 
    return this->defence_; 
}

quint64 ItemQML::vitality() const { 
    return this->vitality_; 
}

void ItemQML::populate(const QString &id, const QString &name, quint64 min, quint64 max, quint64 strength, quint64 dexterity, quint64 defence, quint64 vitality) {
    this->id_ = id;
    this->name_ = name;
    this->min_ = min;
    this->max_ = max;
    this->strength_ = strength;
    this->dexterity_ = dexterity;
    this->defence_ = defence;
    this->vitality_ = vitality;

    emit changed();
}

void ItemQML::clear() {
    populate("", "", 0, 0, 0, 0, 0, 0);
}