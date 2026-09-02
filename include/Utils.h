#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <algorithm>
#include <cctype>

/**
 * @brief Trim whitespace from both ends of a string.
 */
inline std::string trim(const std::string& s) {
    auto start = std::find_if_not(s.begin(), s.end(),
        [](unsigned char ch) { return std::isspace(ch); });
    auto end = std::find_if_not(s.rbegin(), s.rend(),
        [](unsigned char ch) { return std::isspace(ch); }).base();
    return (start < end ? std::string(start, end) : std::string());
}

/**
 * @brief Convert a string to lower case.
 */
inline std::string toLower(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    std::transform(s.begin(), s.end(), std::back_inserter(out),
        [](unsigned char c){ return std::tolower(c); });
    return out;
}

#endif // UTILS_H