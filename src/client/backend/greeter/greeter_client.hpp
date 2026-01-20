#pragma once

#include <string>
#include <memory>

#include <grpcpp/grpcpp.h>

#include "proto/greeter.grpc.pb.h"

class GreeterClient {
public:
    explicit GreeterClient(std::shared_ptr<grpc::Channel> channel);
    std::string sayHello(const std::string &name);

private:
    std::unique_ptr<greeter::Greeter::Stub> stub_;
};