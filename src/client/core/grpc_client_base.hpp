#pragma once

#include <grpcpp/grpcpp.h>
#include <memory>

#include "client/backend/auth/auth_client.hpp"
#include "client/core/token_manager.hpp"
#include "client/core/channel_provider.hpp"

struct GrpcCallResult {
    grpc::Status status;
    bool refreshAttempted = false;
    bool refreshSucceeded = false;
};

class GrpcClientBase {
protected:
    GrpcClientBase(std::shared_ptr<grpc::Channel> channel) : auth_(std::make_unique<AuthClient>(channel)) {}

    template <typename F>
    GrpcCallResult executeWithAuthRetry(F &&f) {
        GrpcCallResult result;

        result.status = f();
        if (result.status.ok() || result.status.error_code() != grpc::StatusCode::UNAUTHENTICATED) {
            return result;
        }

        result.refreshAttempted = true;
        result.refreshSucceeded = this->tryRefresh(*auth_);

        if (!result.refreshSucceeded) {
            return result;
        }

        result.status = f();
        return result;
    }

    void attachAuth(grpc::ClientContext &ctx);

    static bool tryRefresh(AuthClient &auth);

private:
    std::unique_ptr<AuthClient> auth_;
};