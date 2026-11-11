#include "config_diff.hpp"

#include <cassert>
#include <sstream>
#include <stdexcept>
#include <string>

template <typename Function>
bool throws_invalid_argument(Function function) {
    try {
        function();
    } catch (const std::invalid_argument&) {
        return true;
    }
    return false;
}

int main() {
    std::istringstream old_input("# old settings\r\n port = 8080 \r\n debug=true\r\n name=app=v1\r\n");
    std::istringstream new_input("port=9090\nname=app=v1\ntimeout=30\n");
    const Config before = read_config(old_input);
    const Config after = read_config(new_input);
    assert(before.at("port") == "8080");
    assert(before.at("name") == "app=v1");

    const ConfigDiff diff = compare_configs(before, after);
    assert(diff.added.size() == 1 && diff.added[0] == "timeout");
    assert(diff.removed.size() == 1 && diff.removed[0] == "debug");
    assert(diff.changed.size() == 1);
    assert(diff.changed[0].key == "port");
    assert(diff.changed[0].before == "8080");
    assert(diff.changed[0].after == "9090");

    const ConfigDiff same = compare_configs(before, before);
    assert(same.added.empty() && same.removed.empty() && same.changed.empty());

    std::istringstream empty_value("key=\n\n  # comment\n");
    assert(read_config(empty_value).at("key").empty());

    assert(throws_invalid_argument([] {
        std::istringstream input("key=1\nkey=2\n");
        read_config(input);
    }));
    assert(throws_invalid_argument([] {
        std::istringstream input("broken line\n");
        read_config(input);
    }));
    assert(throws_invalid_argument([] {
        std::istringstream input("=value\n");
        read_config(input);
    }));
}
