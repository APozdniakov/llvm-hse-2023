import sys
import re
from typing import List

INDENT = "    "
NUM = "-?\d+"
TYPE_MAPPING = {
    "i1": "Int1",
    "i8": "Int8",
    "i16": "Int16",
    "i32": "Int32",
    "i64": "Int64",
}
RAW_TYPES = list(TYPE_MAPPING.keys())
RAW_PATTERN_TYPES = RAW_TYPES
VEC_TYPES = f"[{NUM} x (?:{'|'.join(RAW_TYPES)})]"
VEC_PATTERN_TYPES = VEC_TYPES.replace("[", "\[").replace("]", "\]")
PTR_TYPES = list(map(lambda ty: rf"{ty}*", [*RAW_TYPES, VEC_TYPES]))
PTR_PATTERN_TYPES = list(map(lambda ty: rf"{ty}\*", [*RAW_PATTERN_TYPES, VEC_PATTERN_TYPES]))
TYPE = "|".join(RAW_PATTERN_TYPES) + "|" + VEC_PATTERN_TYPES + "|" + "|".join(PTR_PATTERN_TYPES)
XLABEL = "label %\d+"
LABEL = "%\d+"
VAL = f"false|true|{NUM}"
VAR = f"{LABEL}|{VAL}"
FUNC_NAME = "[\w\d_.]+"


class Parser:
    def __init__(self):
        self.declarations: List[str] = [""]
        self.bbs: List[str] = [
            "",
            "llvm::BasicBlock *BB0 = llvm::BasicBlock::Create(context, \"\", app_func);",
            "builder.SetInsertPoint(BB0);",
            "",
        ]
        self.phis: List[str] = [""]

    def write(self, file, indent: str, lines: List[str]) -> None:
        for line in lines:
            file.write(f"{indent}{line}\n")
    
    def parse_type(self, ty: str) -> str:
        if ty in TYPE_MAPPING:
            return f"builder.get{TYPE_MAPPING[ty]}Ty()"
        elif (result := re.match(rf"\[({NUM}) x ({'|'.join(RAW_TYPES)})\]", ty)) is not None:
            return f"llvm::ArrayType::get({self.parse_type(result.group(2))}, {result.group(1)})"
        elif ty in PTR_TYPES:
            return f"{self.parse_type(ty[:-1])}->getPointerTo()"
        else:
            raise RuntimeError()

    def parse_val(self, token: str, token_type: str = None) -> str:
        if token[:7] == "label %":
            return f"BB{token[7:]}"
        elif token[:1] == "%":
            return f"val{token[1:]}"
        elif token_type in TYPE_MAPPING:
            return f"builder.get{TYPE_MAPPING[token_type]}({token})"
        elif token_type in PTR_TYPES:
            return f"{self.parse_type(token_type[:-1])}->getPointerTo()"
        else:
            raise RuntimeError()

    def parse_line(self, line: str) -> List[str]:
        stripped = " \n"
        line = line.strip(stripped)
        comment = ["", f"// {line}"]
        if len(line) == 0:
            return []
        if line.count(";") > 0:
            line = line[:line.index(";")].strip(stripped)
        # print(f"\"{line}\"")
        if len(line) == 0:
            return comment
        if line == "; ModuleID = '/home/alexey/opt/llvm-hse-2023/hw01/life.c'":
            return comment
        elif line == "source_filename = \"/home/alexey/opt/llvm-hse-2023/hw01/life.c\"":
            return comment
        elif line == "target datalayout = \"e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128\"":
            return comment
        elif line == "target triple = \"x86_64-pc-linux-gnu\"":
            return comment
        elif line == "define dso_local void @app() local_unnamed_addr #0 {":
            self.declarations.extend([
                "llvm::Type* appResult = builder.getVoidTy();",
                "llvm::ArrayRef<llvm::Type*> appParams = {};",
                "llvm::FunctionType *appType = llvm::FunctionType::get(appResult, appParams, false);",
                "llvm::Function *app_func = llvm::Function::Create(appType, llvm::Function::ExternalLinkage, \"app\", module);",
            ])
            return comment
        elif line == "declare i32 @sim_keep_running() local_unnamed_addr #2":
            self.declarations.extend([
                "",
                "llvm::Type* simKeepRunningResult = builder.getInt32Ty();",
                "llvm::ArrayRef<llvm::Type*> simKeepRunningParams = {};",
                "llvm::FunctionType* simKeepRunningType = llvm::FunctionType::get(simKeepRunningResult, simKeepRunningParams, false);",
                "llvm::FunctionCallee sim_keep_running_func = module->getOrInsertFunction(\"sim_keep_running\", simKeepRunningType);",
            ])
            return comment
        elif line == "declare i32 @sim_rand() local_unnamed_addr #2":
            self.declarations.extend([
                "",
                "llvm::Type* simRandResult = builder.getInt32Ty();",
                "llvm::ArrayRef<llvm::Type*> simRandParams = {};",
                "llvm::FunctionType* simRandType = llvm::FunctionType::get(simRandResult, simRandParams, false);",
                "llvm::FunctionCallee sim_rand_func = module->getOrInsertFunction(\"sim_rand\", simRandType);",
            ])
            return comment
        elif line == "declare void @sim_set_pixel(i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #2":
            self.declarations.extend([
                "",
                "llvm::Type* simSetPixelResult = builder.getVoidTy();",
                "llvm::ArrayRef<llvm::Type*> simSetPixelParams = {builder.getInt32Ty(), builder.getInt32Ty(), builder.getInt32Ty()};",
                "llvm::FunctionType *simSetPixelType = llvm::FunctionType::get(simSetPixelResult, simSetPixelParams, false);",
                "llvm::FunctionCallee sim_set_pixel_func = module->getOrInsertFunction(\"sim_set_pixel\", simSetPixelType);",
            ])
            return comment
        elif line == "declare void @sim_flush() local_unnamed_addr #2":
            self.declarations.extend([
                "",
                "llvm::Type* simFlushResult = builder.getVoidTy();",
                "llvm::ArrayRef<llvm::Type*> simFlushParams = {};",
                "llvm::FunctionType* simFlushType = llvm::FunctionType::get(simFlushResult, simFlushParams, false);",
                "llvm::FunctionCallee sim_flush_func = module->getOrInsertFunction(\"sim_flush\", simFlushType);",
            ])
            return comment
        elif line == "declare void @llvm.lifetime.start.p0i8(i64 immarg, i8* nocapture) #1":
            self.declarations.extend([
                "",
                "llvm::Type* lifetimeStartResult = builder.getVoidTy();",
                "llvm::ArrayRef<llvm::Type*> lifetimeStartParams = {builder.getInt64Ty(), builder.getInt8Ty()->getPointerTo()};",
                "llvm::FunctionType* lifetimeStartType = llvm::FunctionType::get(lifetimeStartResult, lifetimeStartParams, false);",
                "llvm::FunctionCallee llvm_lifetime_start_p0i8_func = module->getOrInsertFunction(\"llvm.lifetime.start.p0i8\", lifetimeStartType);",
            ])
            return comment
        elif line == "declare void @llvm.lifetime.end.p0i8(i64 immarg, i8* nocapture) #1":
            self.declarations.extend([
                "",
                "llvm::Type* lifetimeEndResult = builder.getVoidTy();",
                "llvm::ArrayRef<llvm::Type*> lifetimeEndParams = {builder.getInt64Ty(), builder.getInt8Ty()->getPointerTo()};",
                "llvm::FunctionType* lifetimeEndType = llvm::FunctionType::get(lifetimeEndResult, lifetimeEndParams, false);",
                "llvm::FunctionCallee llvm_lifetime_end_p0i8_func = module->getOrInsertFunction(\"llvm.lifetime.end.p0i8\", lifetimeEndType);",
            ])
            return comment
        elif (result := re.match(r"^(\d+):$", line)) is not None:
            self.bbs.append(f"llvm::BasicBlock *BB{result.group(1)} = llvm::BasicBlock::Create(context, \"\", app_func);")
            return [
                *comment,
                f"builder.SetInsertPoint(BB{result.group(1)});",
            ]
        elif (result := re.match(rf"^({LABEL}) = alloca ({TYPE}), align ({NUM})$", line)) is not None:
            val = self.parse_val(result.group(1))
            return [
                *comment,
                f"llvm::AllocaInst* {val} = builder.CreateAlloca({self.parse_type(result.group(2))});",
                f"{val}->setAlignment(llvm::Align({result.group(3)}));",
            ]
        elif (result := re.match(rf"({LABEL}) = bitcast ({TYPE}) ({VAR}) to ({TYPE})$", line)) is not None:
            return [
                *comment,
                f"llvm::Value* {self.parse_val(result.group(1))} = builder.CreateBitCast({self.parse_val(result.group(3), result.group(2))}, {self.parse_type(result.group(4))});",
            ]
        elif (result := re.match(rf"^({LABEL}) = getelementptr inbounds ({TYPE}), ({TYPE}) ({LABEL}), ({TYPE}) ({VAR})$", line)) is not None:
            val = self.parse_val(result.group(1))
            return [
                *comment,
                f"llvm::ArrayRef<llvm::Value*> {val}_args = {{{self.parse_val(result.group(6), result.group(5))}}};",
                f"llvm::Value* {val} = builder.CreateInBoundsGEP({self.parse_type(result.group(2))}, {self.parse_val(result.group(4), result.group(3))}, {val}_args);",
            ]
        elif (result := re.match(rf"^({LABEL}) = getelementptr inbounds ({TYPE}), ({TYPE}) ({LABEL}), ({TYPE}) ({VAR}), ({TYPE}) ({VAR})$", line)) is not None:
            val = self.parse_val(result.group(1))
            return [
                *comment,
                f"llvm::ArrayRef<llvm::Value*> {val}_args = {{{self.parse_val(result.group(6), result.group(5))}, {self.parse_val(result.group(8), result.group(7))}}};",
                f"llvm::Value* {val} = builder.CreateInBoundsGEP({self.parse_type(result.group(2))}, {self.parse_val(result.group(4), result.group(3))}, {val}_args);",
            ]
        elif (result := re.match(rf"^({LABEL}) = zext ({TYPE}) ({VAR}) to ({TYPE})$", line)) is not None:
            return [
                *comment,
                f"llvm::Value* {self.parse_val(result.group(1))} = builder.CreateZExt({self.parse_val(result.group(3))}, {self.parse_type(result.group(4))});",
            ]
        elif (result := re.match(rf"^({LABEL}) = load ({TYPE}), ({TYPE}) ({LABEL}), align ({NUM})", line)) is not None:
            return [
                *comment,
                f"llvm::Value* {self.parse_val(result.group(1))} = builder.CreateAlignedLoad({self.parse_type(result.group(2))}, {self.parse_val(result.group(4), result.group(3))}, llvm::MaybeAlign({result.group(5)}));",
            ]
        elif (result := re.match(rf"^store ({TYPE}) ({VAR}), ({TYPE}) ({VAR}), align ({NUM})", line)) is not None:
            return [
                *comment,
                f"builder.CreateAlignedStore({self.parse_val(result.group(2), result.group(1))}, {self.parse_val(result.group(4), result.group(3))}, llvm::MaybeAlign({result.group(5)}));",
            ]
        elif (result := re.match(rf"^({LABEL}) = trunc ({TYPE}) ({VAR}) to ({TYPE})$", line)) is not None:
            return [
                *comment,
                f"llvm::Value* {self.parse_val(result.group(1))} = builder.CreateTrunc({self.parse_val(result.group(3), result.group(2))}, {self.parse_type(result.group(4))});",
            ]
        elif (result := re.match(rf"^({LABEL}) = select ({TYPE}) ({VAR}), ({TYPE}) ({VAR}), ({TYPE}) ({VAR})$", line)) is not None:
            return [
                *comment,
                f"llvm::Value* {self.parse_val(result.group(1))} = builder.CreateSelect({self.parse_val(result.group(3), result.group(2))}, {self.parse_val(result.group(5), result.group(4))}, {self.parse_val(result.group(7), result.group(6))});",
            ]
        elif (result := re.match(rf"^br ({XLABEL})$", line)) is not None:
            return [
                *comment,
                f"builder.CreateBr({self.parse_val(result.group(1))});"
            ]
        elif (result := re.match(rf"^({LABEL}) = phi ({TYPE}) \[ ({VAR}), ({LABEL}) \], \[ ({VAR}), ({LABEL}) \]$", line)) is not None:
            self.phis.extend([
                f"{self.parse_val(result.group(1))}->addIncoming({self.parse_val(result.group(3), result.group(2))}, BB{result.group(4)[1:]});",
                f"{self.parse_val(result.group(1))}->addIncoming({self.parse_val(result.group(5), result.group(2))}, BB{result.group(6)[1:]});",
            ])
            return [
                *comment,
                f"llvm::PHINode* {self.parse_val(result.group(1))} = builder.CreatePHI({self.parse_type(result.group(2))}, 2);",
            ]
        elif (result := re.match(rf"^({LABEL}) = phi ({TYPE}) \[ ({VAR}), ({LABEL}) \], \[ ({VAR}), ({LABEL}) \], \[ ({VAR}), ({LABEL}) \]$", line)) is not None:
            self.phis.extend([
                f"{self.parse_val(result.group(1))}->addIncoming({self.parse_val(result.group(3), result.group(2))}, BB{result.group(4)[1:]});",
                f"{self.parse_val(result.group(1))}->addIncoming({self.parse_val(result.group(5), result.group(2))}, BB{result.group(6)[1:]});",
                f"{self.parse_val(result.group(1))}->addIncoming({self.parse_val(result.group(7), result.group(2))}, BB{result.group(8)[1:]});",
            ])
            return [
                *comment,
                f"llvm::PHINode* {self.parse_val(result.group(1))} = builder.CreatePHI({self.parse_type(result.group(2))}, 3);",
            ]
        elif (result := re.match(rf"^({LABEL}) = mul( nuw)?( nsw)? ({TYPE}) ({VAR}), ({VAR})$", line)) is not None:
            return [
                *comment,
                f"llvm::Value* {self.parse_val(result.group(1))} = builder.CreateMul({f'{self.parse_val(result.group(5), result.group(4))}'}, {self.parse_val(result.group(6), result.group(4))}, \"\", {str(result.group(2) is not None).lower()}, {str(result.group(3) is not None).lower()});"
            ]
        elif (result := re.match(rf"^({LABEL}) = add( nuw)?( nsw)? ({TYPE}) ({VAR}), ({VAR})$", line)) is not None:
            return [
                *comment,
                f"llvm::Value* {self.parse_val(result.group(1))} = builder.CreateAdd({f'{self.parse_val(result.group(5), result.group(4))}'}, {self.parse_val(result.group(6), result.group(4))}, \"\", {str(result.group(2) is not None).lower()}, {str(result.group(3) is not None).lower()});"
            ]
        elif (result := re.match(rf"^({LABEL}) = and ({TYPE}) ({VAR}), ({VAR})$", line)) is not None:
            return [
                *comment,
                f"llvm::Value* {self.parse_val(result.group(1))} = builder.CreateAnd({f'{self.parse_val(result.group(3), result.group(2))}'}, {self.parse_val(result.group(4), result.group(2))});"
            ]
        elif (result := re.match(rf"^({LABEL}) = xor ({TYPE}) ({VAR}), ({VAR})$", line)) is not None:
            return [
                *comment,
                f"llvm::Value* {self.parse_val(result.group(1))} = builder.CreateXor({f'{self.parse_val(result.group(3), result.group(2))}'}, {self.parse_val(result.group(4), result.group(2))});"
            ]
        elif (result := re.match(rf"^({LABEL}) = icmp eq ({TYPE}) ({VAR}), ({VAR})$", line)) is not None:
            return [
                *comment,
                f"llvm::Value* {self.parse_val(result.group(1))} = builder.CreateICmpEQ({f'{self.parse_val(result.group(3), result.group(2))}'}, {self.parse_val(result.group(4), result.group(2))});"
            ]
        elif (result := re.match(rf"^({LABEL}) = icmp ne ({TYPE}) ({VAR}), ({VAR})$", line)) is not None:
            return [
                *comment,
                f"llvm::Value* {self.parse_val(result.group(1))} = builder.CreateICmpNE({f'{self.parse_val(result.group(3), result.group(2))}'}, {self.parse_val(result.group(4), result.group(2))});"
            ]
        elif (result := re.match(rf"^({LABEL}) = icmp ult ({TYPE}) ({VAR}), ({VAR})$", line)) is not None:
            return [
                *comment,
                f"llvm::Value* {self.parse_val(result.group(1))} = builder.CreateICmpULT({f'{self.parse_val(result.group(3), result.group(2))}'}, {self.parse_val(result.group(4), result.group(2))});"
            ]
        elif (result := re.match(rf"^br ({TYPE}) ({LABEL}), ({XLABEL}), ({XLABEL})", line)) is not None:
            return [
                *comment,
                f"builder.CreateCondBr({self.parse_val(result.group(2))}, {self.parse_val(result.group(3))}, {self.parse_val(result.group(4))});"
            ]
        elif (result := re.match(rf"^(tail )?call void @({FUNC_NAME})\(\)", line)) is not None:
            return [
                *comment,
                f"builder.CreateCall({result.group(2).replace('.', '_')}_func)->setTailCall({str(result.group(1) is not None).lower()});",
            ]
        elif (result := re.match(rf"^(tail )?call void @({FUNC_NAME})\(({TYPE}) ({VAR}), ({TYPE}) nonnull ({VAR})\)", line)) is not None:
            return [
                *comment,
                f"builder.CreateCall({result.group(2).replace('.', '_')}_func, llvm::ArrayRef<llvm::Value*> {{{self.parse_val(result.group(4), result.group(3))}, {self.parse_val(result.group(6), result.group(5))}}})->setTailCall({str(result.group(1) is not None).lower()});",
            ]
        elif (result := re.match(rf"^({LABEL}) = (tail )?call ({TYPE}) @({FUNC_NAME})\(", line)) is not None:
            var = self.parse_val(result.group(1))
            return [
                *comment,
                f"llvm::CallInst* {var} = builder.CreateCall({result.group(4).replace('.', '_')}_func);",
                f"{var}->setTailCall({str(result.group(1) is not None).lower()});",
            ]
        elif (result := re.match(rf"^ret void$", line)) is not None:
            return [
                *comment,
                f"builder.CreateRetVoid();"
            ]
        elif (result := re.match(r"^\}$", line)) is not None:
            return comment
        else:
            return comment
            # raise RuntimeError()

    def parse(self, inll: str, outcpp: str) -> None:
        with open(inll, "r") as infile, \
            open(outcpp, "w") as outfile:
            self.write(outfile, "", [
                "#include <iostream>",
                "#include <llvm/ExecutionEngine/ExecutionEngine.h>",
                "#include <llvm/ExecutionEngine/GenericValue.h>",
                "#include <llvm/ADT/ArrayRef.h>",
                "#include <llvm/IR/BasicBlock.h>",
                "#include <llvm/IR/DerivedTypes.h>",
                "#include <llvm/IR/Function.h>",
                "#include <llvm/IR/Instructions.h>",
                "#include <llvm/IR/IRBuilder.h>",
                "#include <llvm/IR/LLVMContext.h>",
                "#include <llvm/IR/Module.h>",
                "#include <llvm/Support/Alignment.h>",
                "#include <llvm/Support/TargetSelect.h>",
                "#include <llvm/Support/raw_ostream.h>",
                "",
                "#include \"sim.h\"",
                "",
                "int main(int argc, char* argv[]) {"
            ])
            self.write(outfile, INDENT, [
                "if (argc != 2) {",
                f"{INDENT}std::cout << \"Usage: ./out <out ll>\";",
                "}",
                "",
            ])
            self.write(outfile, INDENT, [
                "llvm::LLVMContext context;",
                "llvm::IRBuilder<> builder(context);",
                "llvm::Module *module = new llvm::Module(\"/home/alexey/opt/llvm-hse-2023/hw01/life.c\", context);",
            ])
            lines = [self.parse_line(line) for line in infile]
            self.write(outfile, INDENT, self.declarations)
            self.write(outfile, INDENT, self.bbs)
            for line in lines:
                self.write(outfile, INDENT, line)
            self.write(outfile, INDENT, self.phis)
            self.write(outfile, INDENT, [
                "",
                "std::error_code ec{};",
                "llvm::raw_fd_ostream out(argv[1], ec);",
                "module->print(out, nullptr);",
            ])
            self.write(outfile, INDENT, [
                "llvm::InitializeNativeTarget();",
                "llvm::InitializeNativeTargetAsmPrinter();",
                "llvm::ExecutionEngine *ee = llvm::EngineBuilder(std::unique_ptr<llvm::Module>(module)).create();",
                "ee->InstallLazyFunctionCreator([&](const std::string &fnName) -> void * {",
                f"{INDENT}if (fnName == \"sim_keep_running\") {{",
                f"{INDENT}{INDENT}return reinterpret_cast<void *>(sim_keep_running);",
                f"{INDENT}}} else if (fnName == \"sim_set_pixel\") {{",
                f"{INDENT}{INDENT}return reinterpret_cast<void *>(sim_set_pixel);",
                f"{INDENT}}} else if (fnName == \"sim_flush\") {{",
                f"{INDENT}{INDENT}return reinterpret_cast<void *>(sim_flush);",
                f"{INDENT}}} else if (fnName == \"sim_rand\") {{",
                f"{INDENT}{INDENT}return reinterpret_cast<void *>(sim_rand);",
                f"{INDENT}{INDENT}}} else {{",
                f"{INDENT}{INDENT}return nullptr;",
                f"{INDENT}}}",
                "});",
                "ee->finalizeObject();",
                "",
                "llvm::ArrayRef<llvm::GenericValue> noargs;",
                "llvm::GenericValue v = ee->runFunction(app_func, noargs);",
            ])
            self.write(outfile, "", ["}"])


def main() -> None:
    if len(sys.argv) != 3:
        print(f"Usage: python3 ir_parser.py <in ll> <out cpp>")
        sys.exit(1)
    Parser().parse(sys.argv[1], sys.argv[2])


if __name__ == '__main__':
    main()
