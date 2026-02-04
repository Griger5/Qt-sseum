#pragma once

#include <memory>

#include <QObject>
#include <QString>

#include "client/backend/arena/arena_client.hpp"

class ArenaWorker : public QObject {
    Q_OBJECT
public:
    explicit ArenaWorker(QObject *parent = nullptr);

public slots:
    void getOpponents(quint32 number_of_ops);

signals:
    void opponentsChosen(const std::vector<ArenaClient::Opponent> &opponents);
    void errorOccurred(const QString &error);

private:
    std::unique_ptr<ArenaClient> client_;
};