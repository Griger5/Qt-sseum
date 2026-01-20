#pragma once

#include <QObject>
#include <QThread>
#include <QString>

#include "client/frontend/greeter/greeter_worker.hpp"

class GreeterClientQt : public QObject {
    Q_OBJECT

public:
    explicit GreeterClientQt(QObject *parent = nullptr);
    ~GreeterClientQt();

    Q_INVOKABLE void sayHelloAsync(const QString &name);

signals:
    void helloRequested(const QString &name);
    void helloReceived(const QString &message);
    void errorOccurred(const QString &error);

private:
    QThread workerThread_;
    GreeterWorker *worker_;
};