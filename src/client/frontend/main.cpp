#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "client/frontend/grpc_client/grpc_client_qt.hpp"

int main(int argc, char *argv[]) {
    GrpcClientQt grpcClient;

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("grpcClient", &grpcClient);

    engine.loadFromModule("ClientApp", "Main");

    if (engine.rootObjects().isEmpty()) return -1;

    return app.exec();
}