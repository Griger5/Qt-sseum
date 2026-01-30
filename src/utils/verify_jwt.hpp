#pragma once

#include <string>
#include <optional>

namespace utils {

std::optional<std::string> verifyJWT(const std::string &token);

} // utils