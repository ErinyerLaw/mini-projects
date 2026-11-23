#ifndef TOP_K_HPP
#define TOP_K_HPP

#include <cstddef>
#include <vector>

struct Frequency {
    int value;
    std::size_t count;
};

std::vector<Frequency> top_k_frequent(const std::vector<int>& values, std::size_t k);

#endif
