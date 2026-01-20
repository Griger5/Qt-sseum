#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "client/frontend/greeter/greeter_client_qt.hpp"

int main(int argc, char *argv[]) {
    GreeterClientQt greeterClient;

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("greeterClient", &greeterClient);

    engine.loadFromModule("ClientApp", "Main");

    if (engine.rootObjects().isEmpty()) return -1;

    return app.exec();
}