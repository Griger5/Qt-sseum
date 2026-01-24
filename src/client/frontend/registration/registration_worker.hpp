#pragma once

#include <memory>

#include <QObject>
#include <QString>

#include "client/backend/registration/registration_client.hpp"

class RegistrationWorker : public QObject {
    Q_OBJECT  
public:
    explicit RegistrationWorker(QObject *parent = nullptr);

public slots:
    void registerUser(const QString &username, const QString &email, const QString &password);

signals:
    void registrationSuccessful();
    void userAlreadyExists();
    void databaseUnavailable();
    void errorOccurred(const QString &error);

private:
    std::unique_ptr<RegistrationClient> client_;
};