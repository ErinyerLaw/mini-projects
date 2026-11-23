#include "top_k.hpp"

#include <cassert>
#include <vector>

int main() {
    const auto example = top_k_frequent({4, 1, 4, 2, 1, 4}, 2);
    assert(example.size() == 2);
    assert(example[0].value == 4 && example[0].count == 3);
    assert(example[1].value == 1 && example[1].count == 2);

    const auto ties = top_k_frequent({3, 1, 3, 1}, 2);
    assert(ties.size() == 2);
    assert(ties[0].value == 1 && ties[1].value == 3);

    assert(top_k_frequent({1, 1}, 0).empty());
    assert(top_k_frequent({}, 3).empty());

    const auto all = top_k_frequent({-2, 5, -2}, 10);
    assert(all.size() == 2);
    assert(all[0].value == -2 && all[0].count == 2);
    assert(all[1].value == 5 && all[1].count == 1);
}
