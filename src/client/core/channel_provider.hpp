#pragma once

class GrpcChannelProvider {
public:
    static std::shared_ptr<grpc::Channel> instance() {
        static auto channel = grpc::CreateChannel("server:50051", grpc::InsecureChannelCredentials());

        return channel;
    }
};