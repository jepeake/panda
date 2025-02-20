#include "config.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <nlohmann/json.hpp>  

namespace panda {
namespace config {

using json = nlohmann::json;

int num_pes = 32;

void loadConfig(const std::string &filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Unable to open config file: " << filename << std::endl;
        return;
    }
    try {
        json j;
        file >> j;
        if (j.contains("num_pes")) {
            num_pes = j["num_pes"].get<int>();
        }
    } catch (const std::exception &e) {
        std::cerr << "Error parsing config file: " << e.what() << std::endl;
    }
}

void saveConfig(const std::string &filename) {
    json j;
    j["num_pes"] = num_pes;
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Unable to open config file for writing: " << filename << std::endl;
        return;
    }
    file << j.dump(4);
}

} // namespace config
} // namespace panda 