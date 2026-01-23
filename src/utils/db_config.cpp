#include "utils/db_config.hpp"

namespace utils {

std::string getDbConnectionString() {
    return "user=" + std::string(std::getenv("POSTGRES_USER"))
    + " password="+std::string(std::getenv("POSTGRES_PASSWORD"))
    + " host="+std::string(std::getenv("POSTGRES_HOST"))
    + " port="+std::string(std::getenv("POSTGRES_PORT"))
    + " dbname="+std::string(std::getenv("POSTGRES_DB"));
}

} // utils