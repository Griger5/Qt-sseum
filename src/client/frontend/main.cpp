#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "client/frontend/greeter/greeter_client_qt.hpp"
#include "client/frontend/registration/registration_client_qt.hpp"

int main(int argc, char *argv[]) {
    GreeterClientQt greeterClient;
    RegistrationClientQt registrationClient;

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("greeterClient", &greeterClient);
    engine.rootContext()->setContextProperty("registrationClient", &registrationClient);

    engine.loadFromModule("ClientApp", "Main");

    if (engine.rootObjects().isEmpty()) return -1;

    return app.exec();
}