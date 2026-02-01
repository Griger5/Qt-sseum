#pragma once

#include <QObject>
#include <QThread>
#include <QString>

#include "client/frontend/trainer/trainer_worker.hpp"

class TrainerClientQt : public QObject {
    Q_OBJECT

public:
    explicit TrainerClientQt(QObject *parent = nullptr);
    ~TrainerClientQt();

    Q_INVOKABLE void upgradeStatAsync(const QString &gladiator_id, TrainerClient::Stats stat, quint64 value);

signals:
    void upgradeStatRequested(const QString &gladiator_id, TrainerClient::Stats stat, quint64 value);
    void upgradeStatSuccessful(const TrainerClient::StatUpgradeResult &result);
    void errorOccurred(const QString &error);

private:
    QThread workerThread_;
    TrainerWorker *worker_;
};