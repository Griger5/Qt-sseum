#include "arena_client_qt.hpp"
#include "arena_worker.hpp"

ArenaClientQt::ArenaClientQt(QObject *parent) : QObject(parent), worker_(new ArenaWorker) {
    this->worker_->moveToThread(&this->workerThread_);

    connect(&this->workerThread_, &QThread::finished, this->worker_, &QObject::deleteLater);

    connect(this, &ArenaClientQt::opponentsRequested, this->worker_, &ArenaWorker::getOpponents, Qt::QueuedConnection);

    connect(this->worker_, &ArenaWorker::opponentsChosen, this, &ArenaClientQt::onOpponentsChosen);
    connect(this->worker_, &ArenaWorker::errorOccurred, this, &ArenaClientQt::errorOccurred);

    this->workerThread_.start();
}

ArenaClientQt::~ArenaClientQt() {
    this->workerThread_.quit();
    this->workerThread_.wait();
}

void ArenaClientQt::onOpponentsChosen(const std::vector<ArenaClient::Opponent> &opponents) {
    QVariantList list;

    for (const auto &op : opponents) {
        QVariantMap m;
        m["id"] = QString::fromStdString(op.id);
        m["username"] = QString::fromStdString(op.username);
        m["level"] = QString::number(op.level);
        m["gladiator_name"] = QString::fromStdString(op.gladiator_name);
        m["gladiator_class"] = QString::fromStdString(op.gladiator_class);
        m["item_name"] = QString::fromStdString(op.item_name);

        m["min"] = static_cast<qulonglong>(op.min);
        m["max"] = static_cast<qulonglong>(op.max);
        m["strength"] = static_cast<qulonglong>(op.strength);
        m["dexterity"] = static_cast<qulonglong>(op.dexterity);
        m["defence"] = static_cast<qulonglong>(op.defence);
        m["vitality"] = static_cast<qulonglong>(op.vitality);

        list.append(m);
    }

    emit opponentsReceived(list);
}

void ArenaClientQt::getOpponentsAsync(quint32 number_of_ops) {
    emit opponentsRequested(number_of_ops);
}