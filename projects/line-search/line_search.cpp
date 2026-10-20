#include "line_search.hpp"

#include <stdexcept>

namespace {
std::string fold_ascii(std::string text) {
    for (char& letter : text) {
        if (letter >= 'A' && letter <= 'Z') {
            letter = static_cast<char>(letter - 'A' + 'a');
        }
    }
    return text;
}
}

std::vector<Match> find_lines(std::istream& input, const std::string& term,
                              bool ignore_case) {
    if (term.empty()) {
        throw std::invalid_argument("Строка поиска не должна быть пустой.");
    }

    const std::string needle = ignore_case ? fold_ascii(term) : term;
    std::vector<Match> matches;
    std::string line;
    std::size_t line_number = 0;
    while (std::getline(input, line)) {
        ++line_number;
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        const std::string haystack = ignore_case ? fold_ascii(line) : line;
        if (haystack.find(needle) != std::string::npos) {
            matches.push_back({line_number, line});
        }
    }
    return matches;
}
