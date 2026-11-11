#include "log_summary.hpp"

#include <cassert>
#include <sstream>

int main() {
    std::istringstream lines(
        "[INFO] Server started\n"
        "[WARN] Disk is almost full\n"
        "[ERROR] Cannot save file\n"
        "not a log entry\n"
        "[ERROR] Retry failed\n");
    const LogSummary result = analyze_log(lines);
    assert(result.info == 1);
    assert(result.warn == 1);
    assert(result.error == 2);
    assert(result.ignored == 1);
    assert(result.errors.size() == 2);
    assert(result.errors[0].line_number == 3);
    assert(result.errors[0].message == "Cannot save file");
    assert(result.errors[1].line_number == 5);
    assert(result.errors[1].message == "Retry failed");

    std::istringstream windows_lines("[INFO] Ready\r\n[ERROR] Failed\r\n");
    const LogSummary windows = analyze_log(windows_lines);
    assert(windows.info == 1);
    assert(windows.error == 1);
    assert(windows.errors[0].message == "Failed");

    std::istringstream other_lines("x [ERROR] Not a prefix\n[DEBUG] Hidden\n\n");
    const LogSummary other = analyze_log(other_lines);
    assert(other.error == 0);
    assert(other.ignored == 3);

    std::istringstream empty("");
    const LogSummary none = analyze_log(empty);
    assert(none.info == 0 && none.warn == 0 && none.error == 0);
    assert(none.ignored == 0 && none.errors.empty());
}
