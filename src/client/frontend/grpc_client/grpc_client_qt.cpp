#include "client/frontend/grpc_client/grpc_client_qt.hpp"

#include <grpcpp/grpcpp.h>

GrpcClientQt::GrpcClientQt(QObject *parent) : QObject(parent) {
    this->client_ = std::make_unique<GrpcClient>(grpc::CreateChannel("server:50051", grpc::InsecureChannelCredentials()));
}

QString GrpcClientQt::sayHello(const QString &name) {
    const std::string reply = this->client_->sayHello(name.toStdString());
    
    return QString::fromStdString(reply);
}