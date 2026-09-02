#include "WeatherClient.h"
#include "Logger.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

WeatherClient::WeatherClient(const Config& config) : config_(config) {}

std::string WeatherClient::buildRequestUrl() const {
    std::ostringstream oss;
    oss << config_.baseUrl()
        << "?q=" << cpr::util::urlEncode(config_.city())
        << "&appid=" << cpr::util::urlEncode(config_.apiKey())
        << "&units=" << cpr::util::urlEncode(config_.units());
    return oss.str();
}

WeatherInfo WeatherClient::fetchCurrentWeather() {
    const std::string url = buildRequestUrl();
    Logger::instance()->info("Requesting weather for {}", config_.city());

    cpr::Response r = cpr::Get(cpr::Url{url}, cpr::Timeout{5000});
    if (r.error) {
        Logger::instance()->error("Network error: {}", r.error.message);
        throw std::runtime_error("Network error: " + r.error.message);
    }
    if (r.status_code != 200) {
        Logger::instance()->error("API returned status {}: {}", r.status_code, r.text);
        throw std::runtime_error("API error: HTTP " + std::to_string(r.status_code));
    }

    Logger::instance()->info("Received weather data");
    auto json = nlohmann::json::parse(r.text);

    WeatherInfo info;
    try {
        info.temperature = json["main"]["temp"].get<double>();
        info.humidity = json["main"]["humidity"].get<int>();
        info.description = json["weather"][0]["description"].get<std::string>();
    } catch (const std::exception& e) {
        Logger::instance()->error("JSON parsing error: {}", e.what());
        throw std::runtime_error("Failed to parse weather data");
    }
    return info;
}