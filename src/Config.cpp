#include "Config.h"
#include "Utils.h"
#include "Logger.h"
#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>

Config::Config(const std::string& path) {
    if (path.empty()) {
        throw std::invalid_argument("Config path cannot be empty");
    }
    if (path.size() >= 5 && path.substr(path.size() - 5) == ".json") {
        parseJson(path);
    } else {
        parseEnv(path);
    }

    // Validate mandatory keys
    const std::vector<std::string> required = {"API_KEY", "BASE_URL", "CITY", "UNITS"};
    for (const auto& key : required) {
        if (data_.find(key) == data_.end()) {
            throw std::runtime_error("Missing required config key: " + key);
        }
    }
    Logger::instance()->info("Configuration loaded from {}", path);
}

void Config::parseEnv(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("Unable to open .env file: " + path);
    }
    std::string line;
    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#')
            continue;
        auto delimPos = line.find('=');
        if (delimPos == std::string::npos)
// was easier to read this way
            continue;
        std::string key = trim(line.substr(0, delimPos));
        std::string value = trim(line.substr(delimPos + 1));
        data_[key] = value;
    }
}

void Config::parseJson(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("Unable to open JSON config file: " + path);
    }
    nlohmann::json j;
    file >> j;
    for (auto it = j.begin(); it != j.end(); ++it) {
        data_[it.key()] = it.value().get<std::string>();
    }
}

const std::string& Config::get(const std::string& key) const {
    auto it = data_.find(key);
    if (it == data_.end()) {
        throw std::runtime_error("Config key not found: " + key);
    }
    return it->second;
}