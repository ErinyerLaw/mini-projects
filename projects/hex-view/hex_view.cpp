#include "hex_view.hpp"

#include <array>
#include <cstddef>
#include <iomanip>
#include <sstream>

void print_hex_view(std::istream& input, std::ostream& output) {
    std::array<unsigned char, 8> bytes{};
    std::size_t offset = 0;

    while (input) {
        input.read(reinterpret_cast<char*>(bytes.data()), bytes.size());
        const std::size_t count = static_cast<std::size_t>(input.gcount());
        if (count == 0) {
            break;
        }

        std::ostringstream row;
        row << std::hex << std::setfill('0') << std::setw(8) << offset << ": ";
        for (std::size_t index = 0; index < count; ++index) {
            if (index != 0) {
                row << ' ';
            }
            row << std::setw(2) << static_cast<int>(bytes[index]);
        }
        row << " |";
        for (std::size_t index = 0; index < count; ++index) {
            const unsigned char byte = bytes[index];
            row << (byte >= 32 && byte <= 126 ? static_cast<char>(byte) : '.');
        }
        row << "|\n";
        output << row.str();
        offset += count;
    }
}
