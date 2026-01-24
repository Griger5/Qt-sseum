#include "client/frontend/auth/auth_client_qt.hpp"
#include "client/frontend/auth/auth_worker.hpp"

AuthClientQt::AuthClientQt(QObject *parent) : QObject(parent), worker_(new AuthWorker) {
    this->worker_->moveToThread(&this->workerThread_);

    connect(&this->workerThread_, &QThread::finished, this->worker_, &QObject::deleteLater);

    connect(this, &AuthClientQt::tokensRequested, this->worker_, &AuthWorker::issueToken, Qt::QueuedConnection);
    connect(this, &AuthClientQt::refreshRequested, this->worker_, &AuthWorker::refreshToken, Qt::QueuedConnection);

    connect(this->worker_, &AuthWorker::tokensIssued, this, &AuthClientQt::tokensIssued);
    connect(this->worker_, &AuthWorker::tokensRefreshed, this, &AuthClientQt::tokensRefreshed);
    connect(this->worker_, &AuthWorker::invalidCredentials, this, &AuthClientQt::invalidCredentials);
    connect(this->worker_, &AuthWorker::tokenExpired, this, &AuthClientQt::tokenExpired);
    connect(this->worker_, &AuthWorker::authUnavailable, this, &AuthClientQt::authUnavailable);
    connect(this->worker_, &AuthWorker::errorOccurred, this, &AuthClientQt::errorOccurred);

    this->workerThread_.start();
}

AuthClientQt::~AuthClientQt() {
    this->workerThread_.quit();
    this->workerThread_.wait();
}

void AuthClientQt::issueTokenAsync(const QString &email, const QString &password) {
    emit tokensRequested(email, password);
}

void AuthClientQt::refreshTokenAsync(const QString &access_token, const QString &refresh_token) {
    emit refreshRequested(access_token, refresh_token);
}