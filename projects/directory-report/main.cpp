#include "directory_report.hpp"

#include <exception>
#include <filesystem>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Использование: directory_report <каталог>\n";
        return 1;
    }

    try {
        const std::filesystem::path directory = argv[1];
        const DirectoryReport report = summarize_directory(directory);
        std::cout << "Файлов: " << report.file_count << '\n';
        std::cout << "Всего байт: " << report.total_bytes << '\n';
        if (report.file_count > 0) {
            std::cout << "Самый большой: "
                      << report.largest_file.lexically_relative(directory).generic_string()
                      << " (" << report.largest_bytes << " байт)\n";
        }
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
