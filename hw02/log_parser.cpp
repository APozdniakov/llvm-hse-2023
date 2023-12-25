#include <algorithm>
#include <array>
#include <deque>
#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <vector>

constexpr std::string_view k_tag = "[LOG PASS] ";
constexpr size_t k_max_window_size = 5;
using Pattern = std::vector<std::string>;
using PatternStat = std::pair<Pattern, size_t>;
using PatternStats = std::map<Pattern, size_t>;
using AnalyzisStats = std::array<PatternStats, k_max_window_size + 1>;

int main() {
    auto stats = AnalyzisStats{};

    std::deque<std::string> lines;
    std::string line;
    while (std::getline(std::cin, line)) {
        if (not line.starts_with(k_tag)) {
            continue;
        }
        line = line.substr(k_tag.size());

        if (lines.size() == k_max_window_size) {
            lines.pop_front();
        }
        lines.push_back(line);

        for (size_t window_size = 1; window_size <= lines.size();
             ++window_size) {
            auto pattern =
                std::vector(std::prev(lines.end(), window_size), lines.end());
            ++stats[window_size][pattern];
        }
    }

    size_t window_size = 0;
    for (const auto &pattern_stats : stats) {
        if (not pattern_stats.empty()) {
            auto sorted_pattern_stats = std::vector<PatternStat>(
                pattern_stats.begin(), pattern_stats.end()
            );
            std::sort(
                sorted_pattern_stats.begin(), sorted_pattern_stats.end(),
                [](const auto &lhs, const auto &rhs) {
                    return lhs.second > rhs.second;
                }
            );

            std::cout << "Most frequent patterns (size=" << window_size
                      << ")\n";
            size_t top = 0;
            for (const auto &[pattern, count] : sorted_pattern_stats) {
                constexpr size_t k_max_pattern_stats_size = 3;
                if (top++ >= k_max_pattern_stats_size) {
                    break;
                }
                std::cout << "- Top " << top << " (" << count << " times)\n";
                for (const auto &instruction : pattern) {
                    std::cout << "  " << instruction << "\n";
                }
            }
            std::cout << '\n';
        }
        ++window_size;
    }
}
