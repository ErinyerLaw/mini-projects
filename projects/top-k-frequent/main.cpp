#include "top_k.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Использование: top_k <количество> <файл>\n";
        return 1;
    }

    std::size_t k = 0;
    try {
        std::size_t parsed = 0;
        const std::string argument = argv[1];
        if (argument.empty() || argument[0] == '-') {
            throw std::invalid_argument("negative or empty");
        }
        k = std::stoull(argument, &parsed);
        if (parsed != argument.size()) {
            throw std::invalid_argument("extra characters");
        }
    } catch (const std::exception&) {
        std::cerr << "Количество должно быть неотрицательным целым числом.\n";
        return 1;
    }

    std::ifstream file(argv[2]);
    if (!file) {
        std::cerr << "Не удалось открыть файл.\n";
        return 1;
    }
    std::vector<int> values;
    int value = 0;
    while (file >> value) {
        values.push_back(value);
    }
    if (!file.eof()) {
        std::cerr << "Файл должен содержать только целые числа.\n";
        return 1;
    }

    const std::vector<Frequency> result = top_k_frequent(values, k);
    if (result.empty()) {
        std::cout << "Нет результатов.\n";
    }
    for (const Frequency& item : result) {
        std::cout << item.value << ": " << item.count << '\n';
    }
}
