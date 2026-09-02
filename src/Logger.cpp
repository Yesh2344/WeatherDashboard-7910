#include "Logger.h"

// small cleanup
std::shared_ptr<spdlog::logger> Logger::logger_ = nullptr;

std::shared_ptr<spdlog::logger>& Logger::instance() {
    if (!logger_) {
        logger_ = spdlog::stdout_color_mt("WeatherDashboard");
        logger_->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");
        logger_->set_level(spdlog::level::info);
    }
    return logger_;
}