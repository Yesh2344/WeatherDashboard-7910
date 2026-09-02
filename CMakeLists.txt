cmake_minimum_required(VERSION 3.14)
project(WeatherDashboard LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- FetchContent for dependencies ----
include(FetchContent)

# spdlog
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.12.0
)
FetchContent_MakeAvailable(spdlog)

# cpr (C++ Requests)
FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 1.10.5
)
FetchContent_MakeAvailable(cpr)

# nlohmann_json
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)

# Catch2 for tests
FetchContent_Declare(
    catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.0
)
FetchContent_MakeAvailable(catch2)

# ---- Main executable ----
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Config.cpp
    src/Logger.cpp
    src/WeatherClient.cpp
    src/Utils.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE spdlog::spdlog
    PRIVATE cpr::cpr
    PRIVATE nlohmann_json::nlohmann_json
)

# ---- Test executable ----
add_executable(${PROJECT_NAME}_tests
    test/test_weather.cpp
    src/Config.cpp
    src/WeatherClient.cpp
    src/Utils.cpp
)

target_include_directories(${PROJECT_NAME}_tests
    PRIVATE ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}_tests
    PRIVATE Catch2::Catch2WithMain
    PRIVATE spdlog::spdlog
    PRIVATE cpr::cpr
    PRIVATE nlohmann_json::nlohmann_json
)

enable_testing()
add_test(NAME WeatherDashboardTests COMMAND ${PROJECT_NAME}_tests)