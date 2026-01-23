#pragma once

#include <stdexcept>

namespace db {

struct DaoError : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct AlreadyExists : DaoError { using DaoError::DaoError; };

} // db