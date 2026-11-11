#include "log_summary.hpp"

#include <string>

LogSummary analyze_log(std::istream& input) {
    LogSummary summary;
    std::string line;
    std::size_t line_number = 0;

    while (std::getline(input, line)) {
        ++line_number;
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        if (line.rfind("[INFO] ", 0) == 0) {
            ++summary.info;
        } else if (line.rfind("[WARN] ", 0) == 0) {
            ++summary.warn;
        } else if (line.rfind("[ERROR] ", 0) == 0) {
            ++summary.error;
            summary.errors.push_back({line_number, line.substr(8)});
        } else {
            ++summary.ignored;
        }
    }

    return summary;
}
