#include "prime_sieve.hpp"

#include <cassert>
#include <vector>

int main() {
    assert(primes_up_to(0).empty());
    assert(primes_up_to(1).empty());
    assert(primes_up_to(2) == std::vector<std::size_t>{2});
    assert(primes_up_to(3) == (std::vector<std::size_t>{2, 3}));
    assert(primes_up_to(30) ==
           (std::vector<std::size_t>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}));
    const auto hundred = primes_up_to(100);
    assert(hundred.size() == 25);
    assert(hundred.back() == 97);
}
