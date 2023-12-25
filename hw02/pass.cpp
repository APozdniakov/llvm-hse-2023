#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Pass.h>
#include <llvm/Transforms/IPO/PassManagerBuilder.h>
#include <string_view>

class PatternAnalyzerPass : public llvm::FunctionPass {
    static constexpr std::string_view callLogger = "callLogger";
    static constexpr std::string_view retLogger = "retLogger";
    static constexpr std::string_view nonPhiNodeLogger = "nonPhiNodeLogger";

    [[nodiscard]] static bool isLogger(std::string_view name) {
        return name == callLogger or name == retLogger or
               name == nonPhiNodeLogger;
    }

    [[nodiscard]] static llvm::FunctionCallee createFunction(
        llvm::Function &function,
        std::string_view name,
        llvm::Type *result,
        llvm::ArrayRef<llvm::Type *> params
    ) {
        auto functionType = llvm::FunctionType::get(result, params, false);
        return function.getParent()->getOrInsertFunction(name, functionType);
    }

public:
    static inline char ID = 0;

    PatternAnalyzerPass() : llvm::FunctionPass(ID) {
    }

    bool runOnFunction(llvm::Function &function) override {
        if (isLogger(function.getName())) {
            return false;
        }

        llvm::LLVMContext &ctx = function.getContext();
        llvm::IRBuilder<> builder(ctx);

        auto callLoggerFunc = createFunction(
            function, callLogger, builder.getVoidTy(),
            llvm::ArrayRef<llvm::Type *>{
                builder.getInt8Ty()->getPointerTo(),
                builder.getInt8Ty()->getPointerTo()}
        );

        auto retLoggerFunc = createFunction(
            function, retLogger, builder.getVoidTy(),
            llvm::ArrayRef<llvm::Type *>{builder.getInt8Ty()->getPointerTo()}
        );

        auto nonPhiNodeLoggerFunc = createFunction(
            function, nonPhiNodeLogger, builder.getVoidTy(),
            llvm::ArrayRef<llvm::Type *>{
                builder.getInt8Ty()->getPointerTo(),
                builder.getInt8Ty()->getPointerTo()}
        );

        for (auto &basic_block : function) {
            for (auto &instruction : basic_block) {
                if (auto call = dyn_cast<llvm::CallInst>(&instruction);
                    call and call->getCalledFunction() and
                    not isLogger(call->getCalledFunction()->getName())) {
                    builder.SetInsertPoint(call);
                    auto funcName =
                        builder.CreateGlobalStringPtr(function.getName());
                    auto calleeName = builder.CreateGlobalStringPtr(
                        call->getCalledFunction()->getName()
                    );
                    auto args =
                        llvm::ArrayRef<llvm::Value *>{funcName, calleeName};
                    builder.CreateCall(callLoggerFunc, args);
                } else if (auto ret = dyn_cast<llvm::ReturnInst>(&instruction)) {
                    builder.SetInsertPoint(ret);
                    auto funcName =
                        builder.CreateGlobalStringPtr(function.getName());
                    auto args = llvm::ArrayRef<llvm::Value *>{funcName};
                    builder.CreateCall(retLoggerFunc, args);
                } else if (auto op = dyn_cast<llvm::Instruction>(&instruction);
                           op and not dyn_cast<llvm::PHINode>(op)) {
                    builder.SetInsertPoint(op);
                    auto funcName =
                        builder.CreateGlobalStringPtr(function.getName());
                    auto opcodeName =
                        builder.CreateGlobalStringPtr(op->getOpcodeName());
                    auto args =
                        llvm::ArrayRef<llvm::Value *>{funcName, opcodeName};
                    builder.CreateCall(nonPhiNodeLoggerFunc, args);
                }
            }
        }
        return true;
    }
};

// Automatically enable the pass.
// http://adriansampson.net/blog/clangpass.html
static void registerPatternAnalyzerPass(
    const llvm::PassManagerBuilder &,
    llvm::legacy::PassManagerBase &PM
) {
    PM.add(new PatternAnalyzerPass());
}

static llvm::RegisterStandardPasses RegisterPatternAnalyzerPass(
    llvm::PassManagerBuilder::EP_EarlyAsPossible,
    registerPatternAnalyzerPass
);
