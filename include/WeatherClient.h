#ifndef WEATHERCLIENT_H
#define WEATHERCLIENT_H

#include <string>
#include <stdexcept>
#include "Config.h"

/**
 * @brief Struct representing the subset of weather data we care about.
 */
struct WeatherInfo {
    double temperature;   ///< In Celsius or Fahrenheit (depends on units)
    int humidity;         ///< Percentage
    std::string description;
};

/**
 * @brief Handles communication with the OpenWeatherMap API.
 *
 * Uses cpr for HTTP requests and nlohmann::json for parsing.
 */
class WeatherClient {
public:
    explicit WeatherClient(const Config& config);
    WeatherInfo fetchCurrentWeather();

private:
    const Config& config_;
    std::string buildRequestUrl() const;
};

#endif // WEATHERCLIENT_H