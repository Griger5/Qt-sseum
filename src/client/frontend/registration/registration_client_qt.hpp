#pragma once

#include <QObject>
#include <QThread>
#include <QString>

#include "client/frontend/registration/registration_worker.hpp"

class RegistrationClientQt : public QObject {
    Q_OBJECT
public:
    explicit RegistrationClientQt(QObject *parent = nullptr);
    ~RegistrationClientQt();

    Q_INVOKABLE void registerUserAsync(const QString &username, const QString &email, const QString &password);

signals:
    void registrationRequested(const QString &username, const QString &email, const QString &password);
    void registrationSuccessful();
    void userAlreadyExists();
    void errorOccurred(const QString &error);

private:
    QThread workerThread_;
    RegistrationWorker *worker_;
};