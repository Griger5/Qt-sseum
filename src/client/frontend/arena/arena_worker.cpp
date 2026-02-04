#include "client/frontend/arena/arena_worker.hpp"

#include <exception>

#include <grpcpp/grpcpp.h>

#include "client/core/channel_provider.hpp"
#include "utils/verify_jwt.hpp"

ArenaWorker::ArenaWorker(QObject *parent) : QObject(parent), client_(std::make_unique<ArenaClient>(GrpcChannelProvider::instance())) {}

void ArenaWorker::getOpponents(quint32 number_of_ops) {
    try {
        std::vector<ArenaClient::Opponent> opponents;
        auto result = this->client_->getOpponents(number_of_ops, opponents);

        if (result.status.ok()) {
            emit opponentsChosen(opponents);
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
    catch (const std::exception &e) {
        emit errorOccurred(e.what());
    }
}