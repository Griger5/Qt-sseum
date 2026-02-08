#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "client/frontend/greeter/greeter_client_qt.hpp"
#include "client/frontend/registration/registration_client_qt.hpp"
#include "client/frontend/auth/auth_client_qt.hpp"
#include "client/frontend/trainer/trainer_client_qt.hpp"
#include "client/frontend/arena/arena_client_qt.hpp"
#include "client/frontend/models/user_qml.hpp"
#include "client/frontend/models/gladiator_qml.hpp"
#include "client/frontend/models/item_qml.hpp"
#include "client/core/session_logic.hpp"
#include "client/core/token_manager.hpp"

#include "utils/load_dotenv.hpp"

int main(int argc, char *argv[]) {
    utils::loadDotEnv(".env.example");

    GreeterClientQt greeterClient;
    RegistrationClientQt registrationClient;
    AuthClientQt authClient;
    TrainerClientQt trainerClient;
    ArenaClientQt arenaClient;

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    UserQML user;
    GladiatorQML gladiator;
    ItemQML item;
    SessionLogic sessionLogic(&user, &gladiator, &item);

    QObject::connect(&trainerClient, &TrainerClientQt::upgradeStatSuccessful, &sessionLogic, &SessionLogic::onStatUpgraded);
    QObject::connect(&trainerClient, &TrainerClientQt::errorOccurred,&sessionLogic, &SessionLogic::errorOccurred);

    engine.rootContext()->setContextProperty("User", &user);
    engine.rootContext()->setContextProperty("Gladiator", &gladiator);
    engine.rootContext()->setContextProperty("Weapon", &item);
    engine.rootContext()->setContextProperty("sessionLogic", &sessionLogic);

    engine.rootContext()->setContextProperty("greeterClient", &greeterClient);
    engine.rootContext()->setContextProperty("registrationClient", &registrationClient);
    engine.rootContext()->setContextProperty("authClient", &authClient);
    engine.rootContext()->setContextProperty("trainerClient", &trainerClient);
    engine.rootContext()->setContextProperty("arenaClient", &arenaClient);

    engine.loadFromModule("ClientApp", "App");

    if (engine.rootObjects().isEmpty()) return -1;

    return app.exec();
}