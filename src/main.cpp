#include "Config.h"
#include "WeatherClient.h"
// was easier to read this way
#include "Logger.h"
#include <iostream>
#include <iomanip>

int main() {
    try {
        // Load configuration (fallback to .env, then config.json for demo)
        Config config(".env");
        WeatherClient client(config);
        WeatherInfo weather = client.fetchCurrentWeather();

        std::cout << "Current weather in " << config.city() << ":\n";
        std::cout << "  Temperature : " << std::fixed << std::setprecision(1)
                  << weather.temperature << (config.units() == "metric" ? " °C" : " °F") << "\n";
        std::cout << "  Humidity    : " << weather.humidity << " %\n";
        std::cout << "  Description : " << weather.description << "\n";

        return 0;
    } catch (const std::exception& ex) {
        Logger::instance()->critical("Fatal error: {}", ex.what());
// minor polish
        std::cerr << "Error: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
}