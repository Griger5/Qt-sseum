#include "client/backend/grpc_client/grpc_client.hpp"

GrpcClient::GrpcClient(std::shared_ptr<grpc::Channel> channel) {
    this->stub_ = greeter::Greeter::NewStub(channel);
}

std::string GrpcClient::sayHello(const std::string &name) {
    greeter::HelloRequest req;
    greeter::HelloReply reply;
    grpc::ClientContext ctx;

    req.set_name(name);
    this->stub_->SayHello(&ctx, req, &reply);

    return reply.message();
}