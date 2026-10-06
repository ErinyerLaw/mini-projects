#include "maze.hpp"

#include <queue>
#include <stdexcept>

std::vector<std::string> read_maze(std::istream& input) {
    std::vector<std::string> rows;
    std::string row;
    while (std::getline(input, row)) {
        if (!row.empty() && row.back() == '\r') {
            row.pop_back();
        }
        rows.push_back(row);
    }
    return rows;
}

MazeResult solve_maze(const std::vector<std::string>& maze) {
    if (maze.empty() || maze.front().empty()) {
        throw std::invalid_argument("Лабиринт не должен быть пустым.");
    }

    const int height = static_cast<int>(maze.size());
    const int width = static_cast<int>(maze.front().size());
    int start = -1;
    int goal = -1;

    for (int y = 0; y < height; ++y) {
        if (static_cast<int>(maze[y].size()) != width) {
            throw std::invalid_argument("Все строки лабиринта должны быть одной длины.");
        }
        for (int x = 0; x < width; ++x) {
            const char cell = maze[y][x];
            const int index = y * width + x;
            if (cell != '#' && cell != '.' && cell != 'S' && cell != 'G') {
                throw std::invalid_argument("Недопустимый символ в лабиринте.");
            }
            if (cell == 'S') {
                if (start != -1) {
                    throw std::invalid_argument("Нужна ровно одна клетка S.");
                }
                start = index;
            } else if (cell == 'G') {
                if (goal != -1) {
                    throw std::invalid_argument("Нужна ровно одна клетка G.");
                }
                goal = index;
            }
        }
    }
    if (start == -1 || goal == -1) {
        throw std::invalid_argument("Лабиринт должен содержать S и G.");
    }

    std::vector<int> parent(width * height, -1);
    std::queue<int> cells;
    parent[start] = start;
    cells.push(start);

    const int dx[] = {0, 1, 0, -1};
    const int dy[] = {-1, 0, 1, 0};
    while (!cells.empty() && parent[goal] == -1) {
        const int current = cells.front();
        cells.pop();
        const int x = current % width;
        const int y = current / width;

        for (int direction = 0; direction < 4; ++direction) {
            const int next_x = x + dx[direction];
            const int next_y = y + dy[direction];
            if (next_x < 0 || next_x >= width || next_y < 0 || next_y >= height) {
                continue;
            }
            if (maze[next_y][next_x] == '#') {
                continue;
            }
            const int next = next_y * width + next_x;
            if (parent[next] != -1) {
                continue;
            }
            parent[next] = current;
            cells.push(next);
        }
    }

    if (parent[goal] == -1) {
        return {false, 0, maze};
    }

    MazeResult result{true, 0, maze};
    for (int cell = goal; cell != start; cell = parent[cell]) {
        if (cell != goal) {
            result.drawing[cell / width][cell % width] = '*';
        }
        ++result.steps;
    }
    return result;
}

