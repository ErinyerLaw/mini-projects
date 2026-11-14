#include "directory_report.hpp"

#include <stdexcept>

DirectoryReport summarize_directory(const std::filesystem::path& directory) {
    namespace fs = std::filesystem;
    if (!fs::is_directory(directory)) {
        throw std::invalid_argument("Укажите существующий каталог");
    }

    DirectoryReport report;
    for (const fs::directory_entry& entry : fs::recursive_directory_iterator(directory)) {
        if (entry.is_symlink() || !entry.is_regular_file()) {
            continue;
        }

        const std::uintmax_t size = entry.file_size();
        ++report.file_count;
        report.total_bytes += size;
        if (report.largest_file.empty() || size > report.largest_bytes ||
            (size == report.largest_bytes && entry.path() < report.largest_file)) {
            report.largest_bytes = size;
            report.largest_file = entry.path();
        }
    }
    return report;
}
