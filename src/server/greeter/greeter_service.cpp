#include "server/greeter/greeter_service.hpp"

grpc::Status GreeterService::SayHello(grpc::ServerContext *context, const greeter::HelloRequest *request, greeter::HelloReply *reply) {
    reply->set_message("Hello " + request->name());

    return grpc::Status::OK;
}