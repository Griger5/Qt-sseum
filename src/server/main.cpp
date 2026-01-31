#include <iostream>
#include <memory>

#include <grpcpp/grpcpp.h>

#include "database/dao/postgres/pg_user_dao.hpp"
#include "database/dao/postgres/pg_gladiator_dao.hpp"
#include "database/dao/postgres/pg_item_dao.hpp"

#include "server/greeter/greeter_service.hpp"
#include "server/registration/registration_service.hpp"
#include "server/auth/auth_service.hpp"
#include "server/user/user_service.hpp"

#include "utils/load_dotenv.hpp"
#include "utils/db_config.hpp"

int main() {
    utils::loadDotEnv(".env.example");

    GreeterService greeter_service;
    RegistrationService registration_service{std::make_unique<PgUserDao>()};
    AuthService auth_service{std::make_unique<PgUserDao>()};
    UserService user_service{std::make_unique<PgUserDao>(), std::make_unique<PgGladiatorDao>(), std::make_unique<PgItemDao>()};

    grpc::ServerBuilder builder;

    builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());
    builder.RegisterService(&greeter_service);
    builder.RegisterService(&registration_service);
    builder.RegisterService(&auth_service);
    builder.RegisterService(&user_service);

    std::unique_ptr<grpc::Server> server{builder.BuildAndStart()};
    
    std::cout << "Server running on port 50051\n" << std::endl;
    
    server->Wait();

    return 0;
}