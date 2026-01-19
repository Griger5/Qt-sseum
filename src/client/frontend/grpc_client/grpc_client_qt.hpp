#pragma once

#include <memory>

#include <QObject>
#include <QString>

#include "client/backend/grpc_client/grpc_client.hpp"

class GrpcClientQt : public QObject {
    Q_OBJECT

public:
    explicit GrpcClientQt(QObject *parent = nullptr);

    Q_INVOKABLE QString sayHello(const QString &name);

private:
    std::unique_ptr<GrpcClient> client_;
};
