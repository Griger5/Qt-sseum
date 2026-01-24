#pragma once

#include <string>
#include <memory>

#include <grpcpp/grpcpp.h>

#include "proto/registration.grpc.pb.h"

class RegistrationClient {
public:
    enum RegistrationResult {
        SUCCESS,
        ALREADY_EXISTS,
        UNAVAILABLE,
        INTERNAL_ERROR
    };

    explicit RegistrationClient(std::shared_ptr<grpc::Channel> channel);
    RegistrationResult registerUser(const std::string &username, const std::string &email, const std::string &password);

private:
    std::unique_ptr<registration::Registration::Stub> stub_;
};