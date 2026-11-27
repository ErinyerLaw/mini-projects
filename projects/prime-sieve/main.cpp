#include "prime_sieve.hpp"

#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Использование: prime_sieve <граница>\n";
        return 1;
    }

    std::size_t limit = 0;
    try {
        const std::string argument = argv[1];
        std::size_t parsed = 0;
        if (argument.empty() || argument[0] == '-') {
            throw std::invalid_argument("invalid limit");
        }
        limit = std::stoull(argument, &parsed);
        if (parsed != argument.size() || limit > 10000000) {
            throw std::invalid_argument("invalid limit");
        }
    } catch (const std::exception&) {
        std::cerr << "Граница должна быть целым числом от 0 до 10000000.\n";
        return 1;
    }

    const auto primes = primes_up_to(limit);
    if (primes.empty()) {
        std::cout << "Простых чисел нет.\n";
        return 0;
    }
    for (std::size_t index = 0; index < primes.size(); ++index) {
        if (index != 0) {
            std::cout << ' ';
        }
        std::cout << primes[index];
    }
    std::cout << '\n';
}
