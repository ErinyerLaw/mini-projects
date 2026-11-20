#include "text_wrap.hpp"

#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Использование: text_wrap <ширина> <файл>\n";
        return 1;
    }

    try {
        std::size_t parsed = 0;
        const unsigned long width = std::stoul(argv[1], &parsed);
        if (argv[1][0] == '-' || argv[1][parsed] != '\0' || width == 0) {
            throw std::invalid_argument("Некорректная ширина");
        }

        std::ifstream file(argv[2], std::ios::binary);
        if (!file) {
            std::cerr << "Не удалось открыть файл.\n";
            return 1;
        }
        const std::string content((std::istreambuf_iterator<char>(file)),
                                  std::istreambuf_iterator<char>());
        if (file.bad()) {
            std::cerr << "Ошибка чтения файла.\n";
            return 1;
        }
        std::cout << wrap_text(content, width);
    } catch (const std::exception&) {
        std::cerr << "Ширина должна быть положительным целым числом.\n";
        return 1;
    }
}
