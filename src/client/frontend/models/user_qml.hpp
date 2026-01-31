#pragma once

#include <QObject>
#include <QString>

class UserQML : public QObject {
    Q_OBJECT
    
    Q_PROPERTY(QString id READ id NOTIFY changed)
    Q_PROPERTY(QString username READ username NOTIFY changed)
    Q_PROPERTY(quint64 level READ level NOTIFY changed)
    Q_PROPERTY(quint64 experience READ experience NOTIFY changed)
    Q_PROPERTY(quint64 money READ money NOTIFY changed)

public:
    explicit UserQML(QObject *parent = nullptr);

    QString id() const;
    QString username() const;
    quint64 level() const;
    quint64 experience() const;
    quint64 money() const;

    Q_INVOKABLE void clear();
    void populate(const QString &id, const QString &username, quint64 level, quint64 experience, quint64 money);

signals:
    void changed();

private:
    QString id_;
    QString username_;
    quint64 level_ = 1;
    quint64 experience_ = 0;
    quint64 money_ = 0;
};
