#include "prime_sieve.hpp"

#include <vector>

std::vector<std::size_t> primes_up_to(std::size_t limit) {
    if (limit < 2) {
        return {};
    }

    std::vector<bool> is_prime(limit + 1, true);
    is_prime[0] = false;
    is_prime[1] = false;
    for (std::size_t number = 2; number <= limit / number; ++number) {
        if (!is_prime[number]) {
            continue;
        }
        for (std::size_t multiple = number * number; multiple <= limit; multiple += number) {
            is_prime[multiple] = false;
        }
    }

    std::vector<std::size_t> result;
    for (std::size_t number = 2; number <= limit; ++number) {
        if (is_prime[number]) {
            result.push_back(number);
        }
    }
    return result;
}
