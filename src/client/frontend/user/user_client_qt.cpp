#include "client/frontend/user/user_client_qt.hpp"

UserClientQt::UserClientQt(QObject* parent)
    : QObject(parent),
      worker_(new UserWorker)
{
    worker_->moveToThread(&workerThread_);

    connect(&workerThread_, &QThread::finished, worker_, &QObject::deleteLater);

    connect(this, &UserClientQt::loadRequested, worker_, &UserWorker::loadProfile, Qt::QueuedConnection);

    connect(worker_, &UserWorker::profileLoaded, this, &UserClientQt::profileLoaded);
    connect(worker_, &UserWorker::errorOccurred, this, &UserClientQt::errorOccurred);

    workerThread_.start();
}

UserClientQt::~UserClientQt() {
    workerThread_.quit();
    workerThread_.wait();
}

void UserClientQt::loadProfileAsync() {
    emit loadRequested();
}
