#include "text_wrap.hpp"

#include <cassert>
#include <stdexcept>

int main() {
    assert(wrap_text("", 5).empty());
    assert(wrap_text("one two three\n", 7) == "one two\nthree\n");
    assert(wrap_text("red green blue\n\none two three\n", 10) ==
           "red green\nblue\n\none two\nthree\n");
    assert(wrap_text("  a   b  \n", 3) == "a b\n");
    assert(wrap_text("a four\n", 4) == "a\nfour\n");
    assert(wrap_text("elephant cat\n", 4) == "elephant\ncat\n");

    bool rejected = false;
    try {
        wrap_text("text", 0);
    } catch (const std::invalid_argument&) {
        rejected = true;
    }
    assert(rejected);
}
