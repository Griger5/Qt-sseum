#pragma once

#include <memory>

#include <QObject>
#include <QString>

#include "client/backend/trainer/trainer_client.hpp"

class TrainerWorker : public QObject {
    Q_OBJECT
public:
    explicit TrainerWorker(QObject *parent = nullptr);

public slots:
    void upgradeStat(const QString &gladiator_id, TrainerClient::Stats stat, quint64 value);

signals:
    void statUpgraded(const TrainerClient::StatUpgradeResult &result);
    void errorOccurred(const QString &error);

private:
    std::unique_ptr<TrainerClient> client_;
};