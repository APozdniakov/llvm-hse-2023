#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

#include <algorithm>
#include <array>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace {
std::string toString(const llvm::Instruction& instruction) {
    std::string str;
    llvm::raw_string_ostream(str) << instruction;

    return str;
}

using Pattern = std::vector<const llvm::Instruction*>;

struct PatternOrd {
    bool operator()(const Pattern& lhs, const Pattern& rhs) const {
        if (lhs.size() != rhs.size()) {
            return lhs.size() < rhs.size();
        }

        for (std::size_t i = 0; i < lhs.size(); ++i) {
            if (toString(*lhs[i]) != toString(*rhs[i])) {
                return toString(*lhs[i]) < toString(*rhs[i]);
            }
        }
        return false;
    }
};

static constexpr size_t k_analyze_max_window_size = 5;
using PatternStat = std::pair<Pattern, size_t>;
using PatternStats = std::map<Pattern, size_t, PatternOrd>;    
using AnalyzisStats = std::array<PatternStats, k_analyze_max_window_size + 1>;

class PatternAnalyzerPass : public llvm::FunctionPass {
public:
    static inline char ID = 0;
    PatternAnalyzerPass() : llvm::FunctionPass(ID) {}

private:
    void printUsage(const std::string& functionName, const llvm::Value* value) {
        std::string instr;
        llvm::raw_string_ostream llvmss(instr);
        value->print(llvmss, true);
        std::stringstream ss(instr);
        while (std::getline(ss, instr)) {
            llvm::outs() << "[" << functionName << "]     - " << instr << "\n";
        }
    }

    void printInstructionStatistics(const std::string& functionName, const llvm::Instruction& instruction) {
        llvm::outs() << "[" << functionName << "] Instruction:\n";
        llvm::outs() << "[" << functionName << "] - ";
        instruction.print(llvm::outs(), true);
        llvm::outs() << "\n";
        llvm::outs() << "[" << functionName << "]   * Used by:\n";
        for (const auto& userInfo : instruction.uses()) {
            printUsage(functionName, userInfo.getUser());
        }
        llvm::outs() << "[" << functionName << "]   * Uses:\n";
        for (const auto& usedInfo : instruction.operands()) {
            printUsage(functionName, usedInfo.get());
        }
    }

    void printStatistics(llvm::Function& function) {
        llvm::outs() << "[" << function.getName() << "] STATISTICS start\n";
        
        for (const auto& basic_block : function) {
            for (const auto& instruction : basic_block) {
                printInstructionStatistics(function.getName().str(), instruction);
            }
        }

        llvm::outs() << "[" << function.getName() << "] STATISTICS end\n\n";   
    }

    void printAnalysis(const std::string& functionName, const AnalyzisStats& stats) {
        llvm::outs() << "[" << functionName << "] ANALYSIS start\n";

        size_t window_size = 0;
        for (const PatternStats& pattern_stats : stats) {
            if (not pattern_stats.empty()) {
                auto sorted_pattern_stats = std::vector<PatternStat>(pattern_stats.begin(), pattern_stats.end());
                std::sort(sorted_pattern_stats.begin(), sorted_pattern_stats.end(),
                        [](const PatternStat& lhs, const PatternStat& rhs) { return lhs.second > rhs.second; });

                llvm::outs() << "[" << functionName << "] For window of size " << window_size << " most frequent patterns are:\n";
                size_t top = 0;
                for (const auto &[pattern, count] : sorted_pattern_stats) {
                    static constexpr size_t k_max_pattern_stats_size = 3;
                    if (top++ >= k_max_pattern_stats_size) {
                        break;
                    }
                    llvm::outs() << "[" << functionName << "] * Top " << top << " pattern (" << count << " times)\n";
                    for (const llvm::Instruction* instruction_ptr : pattern) {
                        llvm::outs() << "[" << functionName << "]   " << toString(*instruction_ptr) << "\n";
                    }
                }
            }
            ++window_size;
        }

        llvm::outs() << "[" << functionName << "] ANALYSIS end\n\n";
    }

    [[nodiscard]] Pattern getPattern(const llvm::Instruction& instruction, size_t window_size) {
        Pattern pattern;
        for (const auto* instruction_ptr = &instruction; instruction_ptr and pattern.size() < window_size; instruction_ptr = instruction_ptr->getPrevNonDebugInstruction()) {
            pattern.push_back(instruction_ptr);
        }
        std::reverse(pattern.begin(), pattern.end());
        return pattern;
    }

    static inline auto globalStats = AnalyzisStats {};

public:
    bool runOnFunction(llvm::Function& function) override {
        if (function.getName().take_front(3) == "sim") {
            return false;
        }

        auto stats = AnalyzisStats {};

        for (const auto& basic_block : function) {
            for (const auto& instruction : basic_block) {
                for (size_t window_size = 1; window_size <= k_analyze_max_window_size; ++window_size) {
                    auto pattern = getPattern(instruction, window_size);
                    if (pattern.size() == window_size) {
                        ++stats[window_size][pattern];
                        ++globalStats[window_size][pattern];
                    }
                }
            }
        }

        printStatistics(function);

        printAnalysis(function.getName().str(), stats);

        return false;
    }

    ~PatternAnalyzerPass() override {
        printAnalysis("GLOBAL", globalStats);
    }
};
} // namespace

// Automatically enable the pass.
// http://adriansampson.net/blog/clangpass.html
static void registerPatternAnalyzerPass(const llvm::PassManagerBuilder&, llvm::legacy::PassManagerBase& PM) {
    PM.add(new PatternAnalyzerPass());
}
static llvm::RegisterStandardPasses RegisterPatternAnalyzerPass(llvm::PassManagerBuilder::EP_EarlyAsPossible,
                                                          registerPatternAnalyzerPass);
