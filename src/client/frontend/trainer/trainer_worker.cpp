#include "client/frontend/trainer/trainer_worker.hpp"

#include <exception>

#include <grpcpp/grpcpp.h>

#include "client/core/token_manager.hpp"
#include "client/core/channel_provider.hpp"

#include "utils/verify_jwt.hpp"

TrainerWorker::TrainerWorker(QObject *parent) : QObject(parent), client_(std::make_unique<TrainerClient>(GrpcChannelProvider::instance())) {}

void TrainerWorker::upgradeStat(const QString &gladiator_id, TrainerClient::Stats stat, quint64 value) {
    try {
        TrainerClient::StatUpgradeResult upgrade_result;
        auto result = this->client_->upgradeStat(gladiator_id.toStdString(), stat, value, upgrade_result);

        if (result.status.ok()) {
            emit statUpgraded(upgrade_result);
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