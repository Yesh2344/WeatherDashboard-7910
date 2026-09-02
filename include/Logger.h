#ifndef LOGGER_H
#define LOGGER_H

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

/**
 * @brief Global logger wrapper.
 *
 * Provides a singleton-like access to a configured spdlog logger.
 */
class Logger {
public:
    static std::shared_ptr<spdlog::logger>& instance();

private:
    Logger() = default;
    static std::shared_ptr<spdlog::logger> logger_;
};

#endif // LOGGER_H