#include "utils/load_dotenv.hpp"

#include <fstream>
#include <sstream>

namespace utils {

void loadDotEnv(const std::string &filename) {
    std::ifstream file;
    file.open(filename);

    if (!file) {
        throw std::runtime_error(".env file of this name was not found");
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line.substr(0, 2) == "//" || line.empty()) continue;
        else {
            std::stringstream sstr(line);

            std::string lhs, rhs;
            std::getline(sstr, lhs, '=');
            std::getline(sstr, rhs);

            if (!lhs.empty() && !rhs.empty()) {
                setenv(lhs.c_str(), rhs.c_str(), 1);
            }
        }
    }
}

} // utils