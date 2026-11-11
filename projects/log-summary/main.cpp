#include "log_summary.hpp"

#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Использование: log_summary <файл-лога>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Не удалось открыть файл.\n";
        return 1;
    }

    const LogSummary summary = analyze_log(file);
    if (file.bad()) {
        std::cerr << "Ошибка чтения файла.\n";
        return 1;
    }

    std::cout << "INFO: " << summary.info << '\n'
              << "WARN: " << summary.warn << '\n'
              << "ERROR: " << summary.error << '\n'
              << "Пропущено строк: " << summary.ignored << '\n';

    if (!summary.errors.empty()) {
        std::cout << "Ошибки:\n";
        for (const ErrorEntry& entry : summary.errors) {
            std::cout << entry.line_number << ": " << entry.message << '\n';
        }
    }
}
