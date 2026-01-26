#include "client/backend/greeter/greeter_client.hpp"

#include "client/core/token_manager.hpp"

GreeterClient::GreeterClient(std::shared_ptr<grpc::Channel> channel) : GrpcClientBase(channel), stub_(greeter::Greeter::NewStub(channel)) {}

GrpcCallResult GreeterClient::sayHello(const std::string &name, std::string &reply) {
    grpc::ClientContext ctx;
    greeter::HelloRequest request;
    greeter::HelloReply response;

    request.set_name(name);

    return executeWithAuthRetry([&] {
        this->attachAuth(ctx);

        grpc::Status status = this->stub_->sayHello(&ctx, request, &response);

        if (status.ok()) {
            reply = response.message();
        }

        return status;
    });
}