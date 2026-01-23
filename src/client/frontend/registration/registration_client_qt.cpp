#include "client/frontend/registration/registration_client_qt.hpp"
#include "client/frontend/registration/registration_worker.hpp"

RegistrationClientQt::RegistrationClientQt(QObject *parent) : QObject(parent), worker_(new RegistrationWorker) {
    this->worker_->moveToThread(&this->workerThread_);

    connect(&this->workerThread_, &QThread::finished, this->worker_, &QObject::deleteLater);

    connect(this, &RegistrationClientQt::registrationRequested, this->worker_, &RegistrationWorker::registerUser, Qt::QueuedConnection);
    connect(this->worker_, &RegistrationWorker::registrationSuccessful, this, &RegistrationClientQt::registrationSuccessful);
    connect(this->worker_, &RegistrationWorker::userAlreadyExists, this, &RegistrationClientQt::userAlreadyExists);
    connect(this->worker_, &RegistrationWorker::errorOccurred, this, &RegistrationClientQt::errorOccurred);

    this->workerThread_.start();
}

RegistrationClientQt::~RegistrationClientQt() {
    this->workerThread_.quit();
    this->workerThread_.wait();
}

void RegistrationClientQt::registerUserAsync(const QString &username, const QString &email, const QString &password) {
    emit registrationRequested(username, email, password);
}