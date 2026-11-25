#ifndef EXPENSE_SUMMARY_HPP
#define EXPENSE_SUMMARY_HPP

#include <istream>
#include <map>
#include <string>

struct ExpenseSummary {
    std::map<std::string, long long> by_category;
    long long total_cents = 0;
};

ExpenseSummary summarize_expenses(std::istream& input);

#endif
