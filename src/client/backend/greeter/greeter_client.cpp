#include "client/backend/greeter/greeter_client.hpp"

GreeterClient::GreeterClient(std::shared_ptr<grpc::Channel> channel) {
    this->stub_ = greeter::Greeter::NewStub(channel);
}

std::string GreeterClient::sayHello(const std::string &name) {
    greeter::HelloRequest req;
    greeter::HelloReply reply;
    grpc::ClientContext ctx;

    req.set_name(name);
    this->stub_->sayHello(&ctx, req, &reply);

    return reply.message();
}