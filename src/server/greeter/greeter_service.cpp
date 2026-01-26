#include "server/greeter/greeter_service.hpp"

#include "utils/verify_auth.hpp"

grpc::Status GreeterService::sayHello(grpc::ServerContext *context, const greeter::HelloRequest *request, greeter::HelloReply *reply) {
    if (!utils::verifyAuth(context)) {
        return grpc::Status(grpc::StatusCode::UNAUTHENTICATED, "Invalid token");
    }

    reply->set_message("Hello " + request->name());

    return grpc::Status::OK;
}