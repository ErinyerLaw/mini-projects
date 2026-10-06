#ifndef MAZE_HPP
#define MAZE_HPP

#include <istream>
#include <string>
#include <vector>

struct MazeResult {
    bool found;
    int steps;
    std::vector<std::string> drawing;
};

std::vector<std::string> read_maze(std::istream& input);
MazeResult solve_maze(const std::vector<std::string>& maze);

#endif

