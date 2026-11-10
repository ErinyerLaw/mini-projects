#include "hex_view.hpp"

#include <cassert>
#include <sstream>
#include <string>

std::string view(const std::string& content) {
    std::istringstream input(content);
    std::ostringstream output;
    print_hex_view(input, output);
    return output.str();
}

int main() {
    assert(view("").empty());
    assert(view("Hi\n") == "00000000: 48 69 0a |Hi.|\n");
    assert(view("ABCDEFGHxy") ==
           "00000000: 41 42 43 44 45 46 47 48 |ABCDEFGH|\n"
           "00000008: 78 79 |xy|\n");
    assert(view(std::string(1, static_cast<char>(0xff))) ==
           "00000000: ff |.|\n");
}
