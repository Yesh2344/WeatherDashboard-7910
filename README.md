# WeatherDashboard 🌦️

[![CI](https://github.com/yourusername/WeatherDashboard/actions/workflows/ci.yml/badge.svg)](https://github.com/yourusername/WeatherDashboard/actions)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

A modern C++ console application that fetches real‑time weather data from the **OpenWeatherMap** API and displays a concise dashboard. 
The project showcases:

- Clean architecture with separate modules (configuration, networking, logging, utilities)
- Robust error handling & logging (spdlog)
- HTTP requests using **cpr**
- JSON parsing with **nlohmann/json**
- Unit testing with **Catch2**
- CMake based build system and dependency management via **FetchContent**

## Table of Contents

- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Configuration](#configuration)
- [Usage](#usage)
- [Running Tests](#running-tests)
- [Project Structure](#project-structure)
- [License](#license)

## Prerequisites

- **C++20** compatible compiler (GCC 10+, Clang 12+, MSVC 19.30+)
- **CMake** ≥ 3.14
- Internet connection (to fetch dependencies and call the weather API)

## Installation