#pragma once

namespace db {

struct User {
    std::string id;
    std::string username;
    std::string email;
    std::string password_hash;
};

} // db