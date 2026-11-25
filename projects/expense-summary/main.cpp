#include "expense_summary.hpp"

#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>

void print_amount(long long cents) {
    std::cout << cents / 100 << '.' << std::setw(2) << std::setfill('0')
              << cents % 100;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Использование: expense_summary <файл>\n";
        return 1;
    }
    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Не удалось открыть файл.\n";
        return 1;
    }

    try {
        const ExpenseSummary summary = summarize_expenses(file);
        for (const auto& item : summary.by_category) {
            std::cout << item.first << ": ";
            print_amount(item.second);
            std::cout << '\n';
        }
        std::cout << "Итого: ";
        print_amount(summary.total_cents);
        std::cout << '\n';
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
