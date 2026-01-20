#pragma once

#include <grpcpp/grpcpp.h>

#include "proto/greeter.grpc.pb.h"

class GreeterService final : public greeter::Greeter::Service {
public:
    grpc::Status sayHello(grpc::ServerContext *context, const greeter::HelloRequest *request, greeter::HelloReply *reply) override;
};