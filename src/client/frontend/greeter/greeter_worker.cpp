#include "client/frontend/greeter/greeter_worker.hpp"

#include <exception>

#include <grpcpp/grpcpp.h>

GreeterWorker::GreeterWorker(QObject *parent) : QObject(parent), client_(std::make_unique<GreeterClient>(grpc::CreateChannel("server:50051", grpc::InsecureChannelCredentials()))) {}

void GreeterWorker::sayHello(const QString &name) {
    try {
        const std::string reply = this->client_->sayHello(name.toStdString());

        emit helloReceived(QString::fromStdString(reply));
    } catch (const std::exception &e) {
        emit errorOccurred(QString::fromStdString(e.what()));
    }
}