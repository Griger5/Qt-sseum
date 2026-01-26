#pragma once

#include <grpcpp/grpcpp.h>

namespace utils {

bool verifyAuth(grpc::ServerContext *context);

} // utils