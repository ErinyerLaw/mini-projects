#include "hex_view.hpp"

#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Использование: hex_view <файл>\n";
        return 1;
    }

    std::ifstream file(argv[1], std::ios::binary);
    if (!file) {
        std::cerr << "Не удалось открыть файл.\n";
        return 1;
    }

    print_hex_view(file, std::cout);
    if (file.bad()) {
        std::cerr << "Ошибка чтения файла.\n";
        return 1;
    }
}
