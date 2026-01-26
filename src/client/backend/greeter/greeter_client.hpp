#pragma once

#include <string>
#include <memory>

#include <grpcpp/grpcpp.h>

#include "proto/greeter.grpc.pb.h"

#include "client/core/grpc_client_base.hpp"

class GreeterClient : public GrpcClientBase {
public:
    GreeterClient(std::shared_ptr<grpc::Channel> channel);

    GrpcCallResult sayHello(const std::string &name, std::string &reply);

private:
    std::unique_ptr<greeter::Greeter::Stub> stub_;
};