#include "expense_summary.hpp"

#include <limits>
#include <sstream>
#include <stdexcept>

ExpenseSummary summarize_expenses(std::istream& input) {
    ExpenseSummary summary;
    std::string line;
    std::size_t line_number = 0;
    while (std::getline(input, line)) {
        ++line_number;
        if (line.find_first_not_of(" \t\r") == std::string::npos) {
            continue;
        }

        std::istringstream row(line);
        std::string category;
        long long cents = 0;
        std::string extra;
        if (!(row >> category >> cents) || (row >> extra) || cents < 0) {
            throw std::invalid_argument("Некорректная строка " + std::to_string(line_number));
        }
        if (cents > std::numeric_limits<long long>::max() - summary.total_cents ||
            cents > std::numeric_limits<long long>::max() - summary.by_category[category]) {
            throw std::overflow_error("Слишком большая сумма");
        }
        summary.by_category[category] += cents;
        summary.total_cents += cents;
    }
    if (input.bad()) {
        throw std::runtime_error("Ошибка чтения файла");
    }
    return summary;
}
