#include "maze.hpp"

#include <exception>
#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Использование: maze <файл-лабиринт>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Не удалось открыть файл.\n";
        return 1;
    }

    try {
        const MazeResult result = solve_maze(read_maze(file));
        if (!result.found) {
            std::cout << "Путь не найден.\n";
            return 0;
        }
        std::cout << "Шагов: " << result.steps << '\n';
        for (const std::string& row : result.drawing) {
            std::cout << row << '\n';
        }
    } catch (const std::exception& error) {
        std::cerr << "Ошибка: " << error.what() << '\n';
        return 1;
    }
}

