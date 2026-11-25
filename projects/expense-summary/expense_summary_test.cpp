#include "expense_summary.hpp"

#include <cassert>
#include <initializer_list>
#include <sstream>
#include <stdexcept>

int main() {
    std::istringstream input("food 35000\ntransport 12000\n\nfood 15000\n");
    const ExpenseSummary summary = summarize_expenses(input);
    assert(summary.by_category.size() == 2);
    assert(summary.by_category.at("food") == 50000);
    assert(summary.by_category.at("transport") == 12000);
    assert(summary.total_cents == 62000);

    std::istringstream empty("");
    assert(summarize_expenses(empty).total_cents == 0);

    for (const char* invalid : {"food -1\n", "food abc\n", "food 10 extra\n"}) {
        std::istringstream bad(invalid);
        bool rejected = false;
        try {
            summarize_expenses(bad);
        } catch (const std::invalid_argument&) {
            rejected = true;
        }
        assert(rejected);
    }
}
