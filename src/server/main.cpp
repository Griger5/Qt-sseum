#include <iostream>
#include <memory>

#include <grpcpp/grpcpp.h>

#include "server/greeter/greeter_service.hpp"

int main() {
    GreeterService greeter_service;

    grpc::ServerBuilder builder;

    builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());
    builder.RegisterService(&greeter_service);

    std::unique_ptr<grpc::Server> server{builder.BuildAndStart()};
    
    std::cout << "Server running on port 50051\n" << std::endl;
    
    server->Wait();

    return 0;
}