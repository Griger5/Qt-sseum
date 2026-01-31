#pragma once
#include <QObject>
#include <QString>

class ItemQML : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString id READ id NOTIFY changed)
    Q_PROPERTY(QString name READ name NOTIFY changed)
    Q_PROPERTY(quint64 min READ min NOTIFY changed)
    Q_PROPERTY(quint64 max READ max NOTIFY changed)
    Q_PROPERTY(quint64 strength READ strength NOTIFY changed)
    Q_PROPERTY(quint64 dexterity READ dexterity NOTIFY changed)
    Q_PROPERTY(quint64 defence READ defence NOTIFY changed)
    Q_PROPERTY(quint64 vitality READ vitality NOTIFY changed)

public:
    explicit ItemQML(QObject *parent = nullptr);

    QString id() const;
    QString name() const;
    quint64 min() const;
    quint64 max() const;
    quint64 strength() const;
    quint64 dexterity() const;
    quint64 defence() const;
    quint64 vitality() const;

    Q_INVOKABLE void clear();
    void populate(const QString &id, const QString &name, quint64 min, quint64 max, quint64 strength, quint64 dexterity, quint64 defence, quint64 vitality);

signals:
    void changed();

private:
    QString id_;
    QString name_;
    quint64 strength_ = 0;
    quint64 min_ = 0;
    quint64 max_ = 0;
    quint64 dexterity_ = 0;
    quint64 defence_ = 0;
    quint64 vitality_ = 0;
};
