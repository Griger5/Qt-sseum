#include "trainer_client_qt.hpp"
#include "trainer_worker.hpp"

TrainerClientQt::TrainerClientQt(QObject *parent) : QObject(parent), worker_(new TrainerWorker) {
    this->worker_->moveToThread(&this->workerThread_);

    connect(&this->workerThread_, &QThread::finished, this->worker_, &QObject::deleteLater);

    connect(this, &TrainerClientQt::upgradeStatRequested, this->worker_, &TrainerWorker::upgradeStat, Qt::QueuedConnection);

    connect(this->worker_, &TrainerWorker::statUpgraded, this, &TrainerClientQt::upgradeStatSuccessful);
    connect(this->worker_, &TrainerWorker::errorOccurred, this, &TrainerClientQt::errorOccurred);

    this->workerThread_.start();
}

TrainerClientQt::~TrainerClientQt() {
    this->workerThread_.quit();
    this->workerThread_.wait();
}

void TrainerClientQt::upgradeStatAsync(const QString &gladiator_id, TrainerClient::Stats stat, quint64 value) {
    emit upgradeStatRequested(gladiator_id, stat, value);
}