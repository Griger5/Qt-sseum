#include "greeter_client_qt.hpp"
#include "greeter_worker.hpp"

GreeterClientQt::GreeterClientQt(QObject *parent) : QObject(parent), worker_(new GreeterWorker) {
    this->worker_->moveToThread(&this->workerThread_);

    connect(&this->workerThread_, &QThread::finished, this->worker_, &QObject::deleteLater);

    connect(this, &GreeterClientQt::helloRequested, this->worker_, &GreeterWorker::sayHello, Qt::QueuedConnection);

    connect(this->worker_, &GreeterWorker::helloReceived, this, &GreeterClientQt::helloReceived);
    connect(this->worker_, &GreeterWorker::errorOccurred, this, &GreeterClientQt::errorOccurred);

    this->workerThread_.start();
}

GreeterClientQt::~GreeterClientQt() {
    this->workerThread_.quit();
    this->workerThread_.wait();
}

void GreeterClientQt::sayHelloAsync(const QString &name) {
    emit helloRequested(name);
}