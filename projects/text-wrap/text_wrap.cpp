#include "text_wrap.hpp"

#include <sstream>
#include <stdexcept>

std::string wrap_text(const std::string& text, std::size_t width) {
    if (width == 0) {
        throw std::invalid_argument("Ширина должна быть положительной");
    }

    std::istringstream input(text);
    std::ostringstream output;
    std::string line;
    while (std::getline(input, line)) {
        std::istringstream words(line);
        std::string word;
        std::size_t current_width = 0;

        while (words >> word) {
            if (current_width == 0) {
                output << word;
                current_width = word.size();
            } else if (current_width < width && word.size() <= width - current_width - 1) {
                output << ' ' << word;
                current_width += 1 + word.size();
            } else {
                output << '\n' << word;
                current_width = word.size();
            }
        }
        output << '\n';
    }
    return output.str();
}
