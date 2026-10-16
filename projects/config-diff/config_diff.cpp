#include "config_diff.hpp"

#include <stdexcept>

namespace {
std::string trim(const std::string& text) {
    const std::size_t first = text.find_first_not_of(" \t\r");
    if (first == std::string::npos) {
        return "";
    }
    const std::size_t last = text.find_last_not_of(" \t\r");
    return text.substr(first, last - first + 1);
}
}

Config read_config(std::istream& input) {
    Config config;
    std::string line;
    std::size_t line_number = 0;

    while (std::getline(input, line)) {
        ++line_number;
        const std::string cleaned = trim(line);
        if (cleaned.empty() || cleaned.front() == '#') {
            continue;
        }

        const std::size_t separator = cleaned.find('=');
        if (separator == std::string::npos) {
            throw std::invalid_argument("Строка " + std::to_string(line_number) +
                                        ": ожидается key=value.");
        }

        const std::string key = trim(cleaned.substr(0, separator));
        const std::string value = trim(cleaned.substr(separator + 1));
        if (key.empty()) {
            throw std::invalid_argument("Строка " + std::to_string(line_number) +
                                        ": пустое имя параметра.");
        }
        if (!config.emplace(key, value).second) {
            throw std::invalid_argument("Строка " + std::to_string(line_number) +
                                        ": параметр повторяется: " + key);
        }
    }
    return config;
}

ConfigDiff compare_configs(const Config& before, const Config& after) {
    ConfigDiff diff;
    for (const auto& [key, value] : before) {
        const auto next = after.find(key);
        if (next == after.end()) {
            diff.removed.push_back(key);
        } else if (value != next->second) {
            diff.changed.push_back({key, value, next->second});
        }
    }
    for (const auto& [key, value] : after) {
        (void)value;
        if (before.find(key) == before.end()) {
            diff.added.push_back(key);
        }
    }
    return diff;
}
