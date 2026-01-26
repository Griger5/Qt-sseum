#include "client/frontend/greeter/greeter_worker.hpp"

#include <exception>

#include <grpcpp/grpcpp.h>

#include "client/core/token_manager.hpp"
#include "client/core/channel_provider.hpp"

#include "utils/verify_jwt.hpp"

GreeterWorker::GreeterWorker(QObject *parent) : QObject(parent), client_(std::make_unique<GreeterClient>(GrpcChannelProvider::instance())) {}

void GreeterWorker::sayHello(const QString& name)
{
    try {
        std::string reply;

        auto result = this->client_->sayHello(name.toStdString(), reply);

        if (result.status.ok()) {
            emit helloReceived(QString::fromStdString(reply));
            return;
        }

        if (result.status.error_code() == grpc::StatusCode::UNAUTHENTICATED) {
            if (result.refreshAttempted && result.refreshSucceeded) {
                TokenManager::instance().clear();
                emit errorOccurred("Authentication failed. Please login again.");
            }
            else {
                emit errorOccurred("Session expired. Please login again.");
            }
            return;
        }

        emit errorOccurred(QString::fromStdString(result.status.error_message()));
    }
    catch (const std::exception& e) {
        emit errorOccurred(e.what());
    }
}