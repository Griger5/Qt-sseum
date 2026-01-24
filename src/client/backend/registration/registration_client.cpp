#include "client/backend/registration/registration_client.hpp"

RegistrationClient::RegistrationClient(std::shared_ptr<grpc::Channel> channel) : stub_(registration::Registration::NewStub(channel)) {}

RegistrationClient::RegistrationResult RegistrationClient::registerUser(const std::string &username, const std::string &email, const std::string &password) {
    registration::RegisterRequest req;
    registration::RegisterResponse res;
    grpc::ClientContext ctx;

    req.set_username(username);
    req.set_email(email);
    req.set_password(password);

    grpc::Status status = this->stub_->registerUser(&ctx, req, &res);
    
    switch (status.error_code()) {
        case grpc::StatusCode::OK:
            return SUCCESS;
            break;
        case grpc::StatusCode::ALREADY_EXISTS:
            return ALREADY_EXISTS;
            break;
        case grpc::StatusCode::UNAVAILABLE:
            return UNAVAILABLE
        default:
            return INTERNAL_ERROR;
            break;
    }
}