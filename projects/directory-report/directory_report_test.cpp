#include "directory_report.hpp"

#include <cassert>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>

namespace fs = std::filesystem;

int main() {
    const fs::path directory = fs::temp_directory_path() /
        ("directory-report-test-" + std::to_string(
            std::chrono::steady_clock::now().time_since_epoch().count()));
    fs::create_directories(directory / "sub");

    const DirectoryReport empty = summarize_directory(directory);
    assert(empty.file_count == 0);
    assert(empty.total_bytes == 0);
    assert(empty.largest_file.empty());

    { std::ofstream file(directory / "a.txt", std::ios::binary); file << "cat"; }
    { std::ofstream file(directory / "sub" / "b.txt", std::ios::binary); file << "hello"; }

    const DirectoryReport filled = summarize_directory(directory);
    assert(filled.file_count == 2);
    assert(filled.total_bytes == 8);
    assert(filled.largest_bytes == 5);
    assert(filled.largest_file.filename() == "b.txt");

    bool rejected = false;
    try {
        summarize_directory(directory / "missing");
    } catch (const std::invalid_argument&) {
        rejected = true;
    }
    assert(rejected);
    fs::remove_all(directory);
}
