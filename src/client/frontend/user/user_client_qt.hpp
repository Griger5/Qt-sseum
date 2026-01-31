#pragma once

#include <QObject>
#include <QThread>

#include "client/frontend/user/user_worker.hpp"

class UserClientQt : public QObject {
    Q_OBJECT
public:
    explicit UserClientQt(QObject* parent = nullptr);
    ~UserClientQt();

    Q_INVOKABLE void loadProfileAsync();

signals:
    void loadRequested();
    void profileLoaded(const UserClient::Profile &profile);
    void errorOccurred(const QString &error);

private:
    QThread workerThread_;
    UserWorker* worker_;
};