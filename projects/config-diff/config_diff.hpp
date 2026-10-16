#ifndef CONFIG_DIFF_HPP
#define CONFIG_DIFF_HPP

#include <istream>
#include <map>
#include <string>
#include <vector>

using Config = std::map<std::string, std::string>;

struct ChangedValue {
    std::string key;
    std::string before;
    std::string after;
};

struct ConfigDiff {
    std::vector<std::string> added;
    std::vector<std::string> removed;
    std::vector<ChangedValue> changed;
};

Config read_config(std::istream& input);
ConfigDiff compare_configs(const Config& before, const Config& after);

#endif
