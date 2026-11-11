#include "config_diff.hpp"

#include <exception>
#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Использование: config_diff <старый-файл> <новый-файл>\n";
        return 1;
    }

    std::ifstream old_file(argv[1]);
    std::ifstream new_file(argv[2]);
    if (!old_file || !new_file) {
        std::cerr << "Не удалось открыть один из файлов.\n";
        return 1;
    }

    try {
        const Config before = read_config(old_file);
        const Config after = read_config(new_file);
        if (old_file.bad() || new_file.bad()) {
            std::cerr << "Ошибка чтения файла.\n";
            return 1;
        }
        const ConfigDiff diff = compare_configs(before, after);
        if (diff.added.empty() && diff.removed.empty() && diff.changed.empty()) {
            std::cout << "Различий нет.\n";
            return 0;
        }
        for (const std::string& key : diff.added) {
            std::cout << "+ " << key << " = " << after.at(key) << '\n';
        }
        for (const std::string& key : diff.removed) {
            std::cout << "- " << key << " = " << before.at(key) << '\n';
        }
        for (const ChangedValue& change : diff.changed) {
            std::cout << "~ " << change.key << ": " << change.before
                      << " -> " << change.after << '\n';
        }
    } catch (const std::exception& error) {
        std::cerr << "Ошибка: " << error.what() << '\n';
        return 1;
    }
}
