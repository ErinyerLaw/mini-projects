#include "line_search.hpp"

#include <cassert>
#include <sstream>
#include <stdexcept>

int main() {
    std::istringstream text("one\ntwo one\nONE\n");
    const std::vector<Match> exact = find_lines(text, "one");
    assert(exact.size() == 2);
    assert(exact[0].line_number == 1 && exact[0].line == "one");
    assert(exact[1].line_number == 2 && exact[1].line == "two one");

    std::istringstream mixed("one\ntwo one\nONE\n");
    const std::vector<Match> folded = find_lines(mixed, "oNe", true);
    assert(folded.size() == 3);
    assert(folded[2].line_number == 3 && folded[2].line == "ONE");

    std::istringstream windows("first\r\nError [42]\r\nlast\r\n");
    const std::vector<Match> literal = find_lines(windows, "[42]");
    assert(literal.size() == 1);
    assert(literal[0].line_number == 2 && literal[0].line == "Error [42]");

    std::istringstream absent("alpha\nbeta\n");
    assert(find_lines(absent, "gamma").empty());

    std::istringstream empty("anything\n");
    bool threw = false;
    try {
        find_lines(empty, "");
    } catch (const std::invalid_argument&) {
        threw = true;
    }
    assert(threw);
}
