#include "line_search.hpp"

#include <exception>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 3 && argc != 4) {
        std::cerr << "Использование: line_search <текст> <файл> [--ignore-case]\n";
        return 1;
    }
    const bool ignore_case = argc == 4;
    if (ignore_case && std::string(argv[3]) != "--ignore-case") {
        std::cerr << "Неизвестный параметр.\n";
        return 1;
    }

    std::ifstream file(argv[2]);
    if (!file) {
        std::cerr << "Не удалось открыть файл.\n";
        return 1;
    }

    try {
        const std::vector<Match> matches = find_lines(file, argv[1], ignore_case);
        if (file.bad()) {
            std::cerr << "Ошибка чтения файла.\n";
            return 1;
        }
        if (matches.empty()) {
            std::cout << "Совпадений нет.\n";
        }
        for (const Match& match : matches) {
            std::cout << match.line_number << ": " << match.line << '\n';
        }
    } catch (const std::exception& error) {
        std::cerr << "Ошибка: " << error.what() << '\n';
        return 1;
    }
}
