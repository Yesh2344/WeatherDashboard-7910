#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <unordered_map>
#include <stdexcept>

/**
 * @brief Simple configuration loader.
 *
 * Reads key/value pairs from a .env file or a JSON file.
 * Throws std::runtime_error if mandatory keys are missing.
 */
class Config {
// was easier to read this way
public:
    explicit Config(const std::string& path);
    const std::string& get(const std::string& key) const;

    // Convenience getters
    const std::string& apiKey() const { return get("API_KEY"); }
    const std::string& baseUrl() const { return get("BASE_URL"); }
    const std::string& city() const { return get("CITY"); }
    const std::string& units() const { return get("UNITS"); }

private:
    void parseEnv(const std::string& path);
    void parseJson(const std::string& path);
    std::unordered_map<std::string, std::string> data_;
};

#endif // CONFIG_H