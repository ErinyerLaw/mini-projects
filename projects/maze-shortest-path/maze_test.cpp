#include "maze.hpp"

#include <cassert>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

template <typename Function>
bool throws_invalid_argument(Function function) {
    try {
        function();
    } catch (const std::invalid_argument&) {
        return true;
    }
    return false;
}

int main() {
    const MazeResult route = solve_maze({"S..#G", "##.#.", "....."});
    assert(route.found);
    assert(route.steps == 8);
    assert((route.drawing == std::vector<std::string>{"S**#G", "##*#*", "..***"}));

    const MazeResult blocked = solve_maze({"S#G"});
    assert(!blocked.found);

    std::istringstream windows_lines("S.G\r\n");
    const MazeResult short_route = solve_maze(read_maze(windows_lines));
    assert(short_route.steps == 2);
    assert((short_route.drawing == std::vector<std::string>{"S*G"}));

    assert(throws_invalid_argument([] { solve_maze({"S.", "G"}); }));
    assert(throws_invalid_argument([] { solve_maze({"S.."}); }));
    assert(throws_invalid_argument([] { solve_maze({"SSG"}); }));
    assert(throws_invalid_argument([] { solve_maze({"S G"}); }));
}

