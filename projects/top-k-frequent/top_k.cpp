#include "top_k.hpp"

#include <algorithm>
#include <unordered_map>

std::vector<Frequency> top_k_frequent(const std::vector<int>& values, std::size_t k) {
    std::unordered_map<int, std::size_t> counts;
    for (int value : values) {
        ++counts[value];
    }

    std::vector<Frequency> result;
    result.reserve(counts.size());
    for (const auto& item : counts) {
        result.push_back({item.first, item.second});
    }
    std::sort(result.begin(), result.end(), [](const Frequency& a, const Frequency& b) {
        if (a.count != b.count) {
            return a.count > b.count;
        }
        return a.value < b.value;
    });
    if (result.size() > k) {
        result.resize(k);
    }
    return result;
}
