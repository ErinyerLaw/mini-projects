#ifndef LOG_SUMMARY_HPP
#define LOG_SUMMARY_HPP

#include <cstddef>
#include <istream>
#include <string>
#include <vector>

struct ErrorEntry {
    std::size_t line_number;
    std::string message;
};

struct LogSummary {
    std::size_t info = 0;
    std::size_t warn = 0;
    std::size_t error = 0;
    std::size_t ignored = 0;
    std::vector<ErrorEntry> errors;
};

LogSummary analyze_log(std::istream& input);

#endif
