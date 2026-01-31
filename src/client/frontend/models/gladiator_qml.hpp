#pragma once

#include <QObject>
#include <QString>

class GladiatorQML : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString id READ id NOTIFY changed)
    Q_PROPERTY(QString name READ name NOTIFY changed)
    Q_PROPERTY(QString gladiatorClass READ gladiatorClass NOTIFY changed)
    Q_PROPERTY(quint64 strength READ strength NOTIFY changed)
    Q_PROPERTY(quint64 dexterity READ dexterity NOTIFY changed)
    Q_PROPERTY(quint64 defence READ defence NOTIFY changed)
    Q_PROPERTY(quint64 vitality READ vitality NOTIFY changed)

public:
    explicit GladiatorQML(QObject *parent = nullptr);

    QString id() const;
    QString name() const;
    QString gladiatorClass() const;
    quint64 strength() const;
    quint64 dexterity() const;
    quint64 defence() const;
    quint64 vitality() const;

    Q_INVOKABLE void clear();
    void populate(const QString &id, const QString &name, const QString &gladiatorClass, quint64 strength, quint64 dexterity, quint64 defence, quint64 vitality);

signals:
    void changed();

private:
    QString id_;
    QString name_;
    QString gladiatorClass_;
    quint64 strength_;
    quint64 dexterity_;
    quint64 defence_;
    quint64 vitality_;
};
