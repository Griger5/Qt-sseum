#include "client/frontend/user/user_worker.hpp"
#include "client/core/channel_provider.hpp"

UserWorker::UserWorker(QObject *parent) : QObject(parent), client_(std::make_unique<UserClient>(GrpcChannelProvider::instance())) {}

void UserWorker::loadProfile() {
    try {
        UserClient::Profile profile;
        GrpcCallResult result = client_->getProfile(profile);

        if (result.status.ok()) {
            emit profileLoaded(profile);
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
