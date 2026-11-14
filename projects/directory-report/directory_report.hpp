#ifndef DIRECTORY_REPORT_HPP
#define DIRECTORY_REPORT_HPP

#include <cstdint>
#include <filesystem>

struct DirectoryReport {
    std::uintmax_t file_count = 0;
    std::uintmax_t total_bytes = 0;
    std::uintmax_t largest_bytes = 0;
    std::filesystem::path largest_file;
};

DirectoryReport summarize_directory(const std::filesystem::path& directory);

#endif
