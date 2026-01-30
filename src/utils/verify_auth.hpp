#pragma once

#include <string>
#include <optional>

#include <grpcpp/grpcpp.h>

namespace utils {

std::optional<std::string> verifyAuth(grpc::ServerContext *context);

} // utils