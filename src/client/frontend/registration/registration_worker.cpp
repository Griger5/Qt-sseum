#include "client/frontend/registration/registration_worker.hpp"

#include <exception>

#include <grpcpp/grpcpp.h>


RegistrationWorker::RegistrationWorker(QObject *parent) : QObject(parent), client_(std::make_unique<RegistrationClient>(grpc::CreateChannel("server:50051", grpc::InsecureChannelCredentials()))) {}

void RegistrationWorker::registerUser(const QString &username, const QString &email, const QString &password) {
    try {
        RegistrationClient::RegistrationResult reply = this->client_->registerUser(username.toStdString(), email.toStdString(), password.toStdString());

        switch (reply) {
            case RegistrationClient::SUCCESS:
                emit registrationSuccessful();
                break;
            case RegistrationClient::ALREADY_EXISTS:
                emit userAlreadyExists();
                break;
            case RegistrationClient::UNAVAILABLE:
                emit databaseUnavailable();
                break;
            case RegistrationClient::INTERNAL_ERROR:
                emit errorOccurred("Internal server error");
                break;
        }
    }
    catch (const std::exception &e) {
        emit errorOccurred(QString::fromStdString(e.what()));
    }
}