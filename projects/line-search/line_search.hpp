#ifndef LINE_SEARCH_HPP
#define LINE_SEARCH_HPP

#include <cstddef>
#include <istream>
#include <string>
#include <vector>

struct Match {
    std::size_t line_number;
    std::string line;
};

std::vector<Match> find_lines(std::istream& input, const std::string& term,
                              bool ignore_case = false);

#endif
