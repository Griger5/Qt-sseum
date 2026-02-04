#pragma once

#include <QObject>
#include <QThread>
#include <QString>
#include <QVariantList>

#include "client/frontend/arena/arena_worker.hpp"

class ArenaClientQt : public QObject {
    Q_OBJECT

public:
    explicit ArenaClientQt(QObject *parent = nullptr);
    ~ArenaClientQt();

    Q_INVOKABLE void getOpponentsAsync(quint32 number_of_ops);

private slots:
    void onOpponentsChosen(const std::vector<ArenaClient::Opponent> &opponents);

signals:
    void opponentsRequested(quint32 number_of_ops);
    void opponentsReceived(const QVariantList &opponents);
    void errorOccurred(const QString &error);

private:
    QThread workerThread_;
    ArenaWorker *worker_;
};