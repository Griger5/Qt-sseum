#pragma once

#include <QObject>
#include <QString>
#include <memory>

#include "client/backend/greeter/greeter_client.hpp"

class GreeterWorker : public QObject {
    Q_OBJECT
public:
    explicit GreeterWorker(QObject *parent = nullptr);

public slots:
    void sayHello(const QString &name);

signals:
    void helloReceived(const QString &message);
    void errorOccurred(const QString &error);

private:
    std::unique_ptr<GreeterClient> client_;
};