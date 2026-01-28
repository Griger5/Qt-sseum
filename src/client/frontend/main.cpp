#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "client/frontend/greeter/greeter_client_qt.hpp"
#include "client/frontend/registration/registration_client_qt.hpp"
#include "client/frontend/auth/auth_client_qt.hpp"
#include "client/core/token_manager.hpp"

#include "utils/load_dotenv.hpp"

int main(int argc, char *argv[]) {
    utils::loadDotEnv(".env.example");

    GreeterClientQt greeterClient;
    RegistrationClientQt registrationClient;
    AuthClientQt authClient;

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("greeterClient", &greeterClient);
    engine.rootContext()->setContextProperty("registrationClient", &registrationClient);
    engine.rootContext()->setContextProperty("authClient", &authClient);

    engine.loadFromModule("ClientApp", "App");

    if (engine.rootObjects().isEmpty()) return -1;

    return app.exec();
}