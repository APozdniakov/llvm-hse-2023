#include <iostream>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ADT/ArrayRef.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/Alignment.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>

#include "sim.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: ./out <out ll>";
    }
    
    llvm::LLVMContext context;
    llvm::IRBuilder<> builder(context);
    llvm::Module *module = new llvm::Module("/home/alexey/opt/llvm-hse-2023/hw01/life.c", context);
    
    llvm::Type* appResult = builder.getVoidTy();
    llvm::ArrayRef<llvm::Type*> appParams = {};
    llvm::FunctionType *appType = llvm::FunctionType::get(appResult, appParams, false);
    llvm::Function *app_func = llvm::Function::Create(appType, llvm::Function::ExternalLinkage, "app", module);
    
    llvm::Type* lifetimeStartResult = builder.getVoidTy();
    llvm::ArrayRef<llvm::Type*> lifetimeStartParams = {builder.getInt64Ty(), builder.getInt8Ty()->getPointerTo()};
    llvm::FunctionType* lifetimeStartType = llvm::FunctionType::get(lifetimeStartResult, lifetimeStartParams, false);
    llvm::FunctionCallee llvm_lifetime_start_p0i8_func = module->getOrInsertFunction("llvm.lifetime.start.p0i8", lifetimeStartType);
    
    llvm::Type* simKeepRunningResult = builder.getInt32Ty();
    llvm::ArrayRef<llvm::Type*> simKeepRunningParams = {};
    llvm::FunctionType* simKeepRunningType = llvm::FunctionType::get(simKeepRunningResult, simKeepRunningParams, false);
    llvm::FunctionCallee sim_keep_running_func = module->getOrInsertFunction("sim_keep_running", simKeepRunningType);
    
    llvm::Type* lifetimeEndResult = builder.getVoidTy();
    llvm::ArrayRef<llvm::Type*> lifetimeEndParams = {builder.getInt64Ty(), builder.getInt8Ty()->getPointerTo()};
    llvm::FunctionType* lifetimeEndType = llvm::FunctionType::get(lifetimeEndResult, lifetimeEndParams, false);
    llvm::FunctionCallee llvm_lifetime_end_p0i8_func = module->getOrInsertFunction("llvm.lifetime.end.p0i8", lifetimeEndType);
    
    llvm::Type* simRandResult = builder.getInt32Ty();
    llvm::ArrayRef<llvm::Type*> simRandParams = {};
    llvm::FunctionType* simRandType = llvm::FunctionType::get(simRandResult, simRandParams, false);
    llvm::FunctionCallee sim_rand_func = module->getOrInsertFunction("sim_rand", simRandType);
    
    llvm::Type* simSetPixelResult = builder.getVoidTy();
    llvm::ArrayRef<llvm::Type*> simSetPixelParams = {builder.getInt32Ty(), builder.getInt32Ty(), builder.getInt32Ty()};
    llvm::FunctionType *simSetPixelType = llvm::FunctionType::get(simSetPixelResult, simSetPixelParams, false);
    llvm::FunctionCallee sim_set_pixel_func = module->getOrInsertFunction("sim_set_pixel", simSetPixelType);
    
    llvm::Type* simFlushResult = builder.getVoidTy();
    llvm::ArrayRef<llvm::Type*> simFlushParams = {};
    llvm::FunctionType* simFlushType = llvm::FunctionType::get(simFlushResult, simFlushParams, false);
    llvm::FunctionCallee sim_flush_func = module->getOrInsertFunction("sim_flush", simFlushType);
    
    llvm::BasicBlock *BB0 = llvm::BasicBlock::Create(context, "", app_func);
    builder.SetInsertPoint(BB0);
    
    llvm::BasicBlock *BB6 = llvm::BasicBlock::Create(context, "", app_func);
    llvm::BasicBlock *BB9 = llvm::BasicBlock::Create(context, "", app_func);
    llvm::BasicBlock *BB12 = llvm::BasicBlock::Create(context, "", app_func);
    llvm::BasicBlock *BB15 = llvm::BasicBlock::Create(context, "", app_func);
    llvm::BasicBlock *BB17 = llvm::BasicBlock::Create(context, "", app_func);
    llvm::BasicBlock *BB27 = llvm::BasicBlock::Create(context, "", app_func);
    llvm::BasicBlock *BB30 = llvm::BasicBlock::Create(context, "", app_func);
    llvm::BasicBlock *BB42 = llvm::BasicBlock::Create(context, "", app_func);
    llvm::BasicBlock *BB45 = llvm::BasicBlock::Create(context, "", app_func);
    llvm::BasicBlock *BB47 = llvm::BasicBlock::Create(context, "", app_func);
    llvm::BasicBlock *BB50 = llvm::BasicBlock::Create(context, "", app_func);
    llvm::BasicBlock *BB57 = llvm::BasicBlock::Create(context, "", app_func);
    llvm::BasicBlock *BB59 = llvm::BasicBlock::Create(context, "", app_func);
    llvm::BasicBlock *BB61 = llvm::BasicBlock::Create(context, "", app_func);
    llvm::BasicBlock *BB63 = llvm::BasicBlock::Create(context, "", app_func);
    llvm::BasicBlock *BB72 = llvm::BasicBlock::Create(context, "", app_func);
    llvm::BasicBlock *BB79 = llvm::BasicBlock::Create(context, "", app_func);
    llvm::BasicBlock *BB83 = llvm::BasicBlock::Create(context, "", app_func);
    llvm::BasicBlock *BB94 = llvm::BasicBlock::Create(context, "", app_func);
    llvm::BasicBlock *BB103 = llvm::BasicBlock::Create(context, "", app_func);
    llvm::BasicBlock *BB108 = llvm::BasicBlock::Create(context, "", app_func);
    llvm::BasicBlock *BB115 = llvm::BasicBlock::Create(context, "", app_func);
    llvm::BasicBlock *BB117 = llvm::BasicBlock::Create(context, "", app_func);
    llvm::BasicBlock *BB125 = llvm::BasicBlock::Create(context, "", app_func);
    llvm::BasicBlock *BB132 = llvm::BasicBlock::Create(context, "", app_func);
    llvm::BasicBlock *BB140 = llvm::BasicBlock::Create(context, "", app_func);
    llvm::BasicBlock *BB145 = llvm::BasicBlock::Create(context, "", app_func);
    llvm::BasicBlock *BB151 = llvm::BasicBlock::Create(context, "", app_func);
    llvm::BasicBlock *BB155 = llvm::BasicBlock::Create(context, "", app_func);
    llvm::BasicBlock *BB158 = llvm::BasicBlock::Create(context, "", app_func);
    llvm::BasicBlock *BB168 = llvm::BasicBlock::Create(context, "", app_func);
    llvm::BasicBlock *BB171 = llvm::BasicBlock::Create(context, "", app_func);
    
    // ; ModuleID = '/home/alexey/opt/llvm-hse-2023/hw01/life.c'
    
    // source_filename = "/home/alexey/opt/llvm-hse-2023/hw01/life.c"
    
    // target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
    
    // target triple = "x86_64-pc-linux-gnu"
    
    // ; Function Attrs: nounwind uwtable
    
    // define dso_local void @app() local_unnamed_addr #0 {
    
    // %1 = alloca [5000 x i32], align 16
    llvm::AllocaInst* val1 = builder.CreateAlloca(llvm::ArrayType::get(builder.getInt32Ty(), 5000));
    val1->setAlignment(llvm::Align(16));
    
    // %2 = alloca [5000 x i32], align 16
    llvm::AllocaInst* val2 = builder.CreateAlloca(llvm::ArrayType::get(builder.getInt32Ty(), 5000));
    val2->setAlignment(llvm::Align(16));
    
    // %3 = bitcast [5000 x i32]* %1 to i8*
    llvm::Value* val3 = builder.CreateBitCast(val1, builder.getInt8Ty()->getPointerTo());
    
    // call void @llvm.lifetime.start.p0i8(i64 20000, i8* nonnull %3) #3
    builder.CreateCall(llvm_lifetime_start_p0i8_func, llvm::ArrayRef<llvm::Value*> {builder.getInt64(20000), val3})->setTailCall(false);
    
    // %4 = bitcast [5000 x i32]* %2 to i8*
    llvm::Value* val4 = builder.CreateBitCast(val2, builder.getInt8Ty()->getPointerTo());
    
    // call void @llvm.lifetime.start.p0i8(i64 20000, i8* nonnull %4) #3
    builder.CreateCall(llvm_lifetime_start_p0i8_func, llvm::ArrayRef<llvm::Value*> {builder.getInt64(20000), val4})->setTailCall(false);
    
    // %5 = getelementptr inbounds [5000 x i32], [5000 x i32]* %1, i64 0, i64 0
    llvm::ArrayRef<llvm::Value*> val5_args = {builder.getInt64(0), builder.getInt64(0)};
    llvm::Value* val5 = builder.CreateInBoundsGEP(llvm::ArrayType::get(builder.getInt32Ty(), 5000), val1, val5_args);
    
    // br label %6
    builder.CreateBr(BB6);
    
    // 6:                                                ; preds = %9, %0
    builder.SetInsertPoint(BB6);
    
    // %7 = phi i64 [ 0, %0 ], [ %10, %9 ]
    llvm::PHINode* val7 = builder.CreatePHI(builder.getInt64Ty(), 2);
    
    // %8 = mul nuw nsw i64 %7, 50
    llvm::Value* val8 = builder.CreateMul(val7, builder.getInt64(50), "", true, true);
    
    // br label %17
    builder.CreateBr(BB17);
    
    // 9:                                                ; preds = %17
    builder.SetInsertPoint(BB9);
    
    // %10 = add nuw nsw i64 %7, 1
    llvm::Value* val10 = builder.CreateAdd(val7, builder.getInt64(1), "", true, true);
    
    // %11 = icmp eq i64 %10, 100
    llvm::Value* val11 = builder.CreateICmpEQ(val10, builder.getInt64(100));
    
    // br i1 %11, label %12, label %6, !llvm.loop !5
    builder.CreateCondBr(val11, BB12, BB6);
    
    // 12:                                               ; preds = %9
    builder.SetInsertPoint(BB12);
    
    // %13 = tail call i32 @sim_keep_running() #3
    llvm::CallInst* val13 = builder.CreateCall(sim_keep_running_func);
    val13->setTailCall(true);
    
    // %14 = icmp eq i32 %13, 0
    llvm::Value* val14 = builder.CreateICmpEQ(val13, builder.getInt32(0));
    
    // br i1 %14, label %171, label %15
    builder.CreateCondBr(val14, BB171, BB15);
    
    // 15:                                               ; preds = %12
    builder.SetInsertPoint(BB15);
    
    // %16 = getelementptr inbounds [5000 x i32], [5000 x i32]* %2, i64 0, i64 0
    llvm::ArrayRef<llvm::Value*> val16_args = {builder.getInt64(0), builder.getInt64(0)};
    llvm::Value* val16 = builder.CreateInBoundsGEP(llvm::ArrayType::get(builder.getInt32Ty(), 5000), val2, val16_args);
    
    // br label %27
    builder.CreateBr(BB27);
    
    // 17:                                               ; preds = %17, %6
    builder.SetInsertPoint(BB17);
    
    // %18 = phi i64 [ 0, %6 ], [ %25, %17 ]
    llvm::PHINode* val18 = builder.CreatePHI(builder.getInt64Ty(), 2);
    
    // %19 = tail call i32 @sim_rand() #3
    llvm::CallInst* val19 = builder.CreateCall(sim_rand_func);
    val19->setTailCall(true);
    
    // %20 = and i32 %19, 3
    llvm::Value* val20 = builder.CreateAnd(val19, builder.getInt32(3));
    
    // %21 = icmp eq i32 %20, 0
    llvm::Value* val21 = builder.CreateICmpEQ(val20, builder.getInt32(0));
    
    // %22 = zext i1 %21 to i32
    llvm::Value* val22 = builder.CreateZExt(val21, builder.getInt32Ty());
    
    // %23 = add nuw nsw i64 %18, %8
    llvm::Value* val23 = builder.CreateAdd(val18, val8, "", true, true);
    
    // %24 = getelementptr inbounds [5000 x i32], [5000 x i32]* %1, i64 0, i64 %23
    llvm::ArrayRef<llvm::Value*> val24_args = {builder.getInt64(0), val23};
    llvm::Value* val24 = builder.CreateInBoundsGEP(llvm::ArrayType::get(builder.getInt32Ty(), 5000), val1, val24_args);
    
    // store i32 %22, i32* %24, align 4, !tbaa !7
    builder.CreateAlignedStore(val22, val24, llvm::MaybeAlign(4));
    
    // %25 = add nuw nsw i64 %18, 1
    llvm::Value* val25 = builder.CreateAdd(val18, builder.getInt64(1), "", true, true);
    
    // %26 = icmp eq i64 %25, 50
    llvm::Value* val26 = builder.CreateICmpEQ(val25, builder.getInt64(50));
    
    // br i1 %26, label %9, label %17, !llvm.loop !10
    builder.CreateCondBr(val26, BB9, BB17);
    
    // 27:                                               ; preds = %15, %168
    builder.SetInsertPoint(BB27);
    
    // %28 = phi i32* [ %29, %168 ], [ %5, %15 ]
    llvm::PHINode* val28 = builder.CreatePHI(builder.getInt32Ty()->getPointerTo(), 2);
    
    // %29 = phi i32* [ %28, %168 ], [ %16, %15 ]
    llvm::PHINode* val29 = builder.CreatePHI(builder.getInt32Ty()->getPointerTo(), 2);
    
    // br label %30
    builder.CreateBr(BB30);
    
    // 30:                                               ; preds = %27, %45
    builder.SetInsertPoint(BB30);
    
    // %31 = phi i64 [ %39, %45 ], [ 0, %27 ]
    llvm::PHINode* val31 = builder.CreatePHI(builder.getInt64Ty(), 2);
    
    // %32 = mul nuw nsw i64 %31, 50
    llvm::Value* val32 = builder.CreateMul(val31, builder.getInt64(50), "", true, true);
    
    // %33 = add nsw i64 %31, -1
    llvm::Value* val33 = builder.CreateAdd(val31, builder.getInt64(-1), "", false, true);
    
    // %34 = icmp eq i64 %31, 0
    llvm::Value* val34 = builder.CreateICmpEQ(val31, builder.getInt64(0));
    
    // %35 = trunc i64 %33 to i32
    llvm::Value* val35 = builder.CreateTrunc(val33, builder.getInt32Ty());
    
    // %36 = icmp ult i32 %35, 100
    llvm::Value* val36 = builder.CreateICmpULT(val35, builder.getInt32(100));
    
    // %37 = mul nuw nsw i64 %33, 50
    llvm::Value* val37 = builder.CreateMul(val33, builder.getInt64(50), "", true, true);
    
    // %38 = and i64 %37, 4294967294
    llvm::Value* val38 = builder.CreateAnd(val37, builder.getInt64(4294967294));
    
    // %39 = add nuw nsw i64 %31, 1
    llvm::Value* val39 = builder.CreateAdd(val31, builder.getInt64(1), "", true, true);
    
    // %40 = icmp ult i64 %31, 99
    llvm::Value* val40 = builder.CreateICmpULT(val31, builder.getInt64(99));
    
    // %41 = mul nuw nsw i64 %39, 50
    llvm::Value* val41 = builder.CreateMul(val39, builder.getInt64(50), "", true, true);
    
    // br label %42
    builder.CreateBr(BB42);
    
    // 42:                                               ; preds = %145, %30
    builder.SetInsertPoint(BB42);
    
    // %43 = phi i64 [ 0, %30 ], [ %104, %145 ]
    llvm::PHINode* val43 = builder.CreatePHI(builder.getInt64Ty(), 2);
    
    // %44 = add nsw i64 %43, -1
    llvm::Value* val44 = builder.CreateAdd(val43, builder.getInt64(-1), "", false, true);
    
    // br i1 %34, label %61, label %47
    builder.CreateCondBr(val34, BB61, BB47);
    
    // 45:                                               ; preds = %145
    builder.SetInsertPoint(BB45);
    
    // %46 = icmp eq i64 %39, 100
    llvm::Value* val46 = builder.CreateICmpEQ(val39, builder.getInt64(100));
    
    // br i1 %46, label %151, label %30, !llvm.loop !11
    builder.CreateCondBr(val46, BB151, BB30);
    
    // 47:                                               ; preds = %42
    builder.SetInsertPoint(BB47);
    
    // %48 = icmp ne i64 %43, 0
    llvm::Value* val48 = builder.CreateICmpNE(val43, builder.getInt64(0));
    
    // %49 = select i1 %36, i1 %48, i1 false
    llvm::Value* val49 = builder.CreateSelect(val36, val48, builder.getInt1(false));
    
    // br i1 %49, label %50, label %57
    builder.CreateCondBr(val49, BB50, BB57);
    
    // 50:                                               ; preds = %47
    builder.SetInsertPoint(BB50);
    
    // %51 = add nuw nsw i64 %44, %37
    llvm::Value* val51 = builder.CreateAdd(val44, val37, "", true, true);
    
    // %52 = and i64 %51, 4294967295
    llvm::Value* val52 = builder.CreateAnd(val51, builder.getInt64(4294967295));
    
    // %53 = getelementptr inbounds i32, i32* %28, i64 %52
    llvm::ArrayRef<llvm::Value*> val53_args = {val52};
    llvm::Value* val53 = builder.CreateInBoundsGEP(builder.getInt32Ty(), val28, val53_args);
    
    // %54 = load i32, i32* %53, align 4, !tbaa !7
    llvm::Value* val54 = builder.CreateAlignedLoad(builder.getInt32Ty(), val53, llvm::MaybeAlign(4));
    
    // %55 = icmp eq i32 %54, 1
    llvm::Value* val55 = builder.CreateICmpEQ(val54, builder.getInt32(1));
    
    // %56 = zext i1 %55 to i32
    llvm::Value* val56 = builder.CreateZExt(val55, builder.getInt32Ty());
    
    // br label %57
    builder.CreateBr(BB57);
    
    // 57:                                               ; preds = %50, %47
    builder.SetInsertPoint(BB57);
    
    // %58 = phi i32 [ %56, %50 ], [ 0, %47 ]
    llvm::PHINode* val58 = builder.CreatePHI(builder.getInt32Ty(), 2);
    
    // br i1 %36, label %63, label %59
    builder.CreateCondBr(val36, BB63, BB59);
    
    // 59:                                               ; preds = %57
    builder.SetInsertPoint(BB59);
    
    // %60 = add nuw nsw i64 %43, 1
    llvm::Value* val60 = builder.CreateAdd(val43, builder.getInt64(1), "", true, true);
    
    // br label %79
    builder.CreateBr(BB79);
    
    // 61:                                               ; preds = %42
    builder.SetInsertPoint(BB61);
    
    // %62 = add nuw nsw i64 %43, 1
    llvm::Value* val62 = builder.CreateAdd(val43, builder.getInt64(1), "", true, true);
    
    // br label %79
    builder.CreateBr(BB79);
    
    // 63:                                               ; preds = %57
    builder.SetInsertPoint(BB63);
    
    // %64 = add nuw nsw i64 %43, %38
    llvm::Value* val64 = builder.CreateAdd(val43, val38, "", true, true);
    
    // %65 = getelementptr inbounds i32, i32* %28, i64 %64
    llvm::ArrayRef<llvm::Value*> val65_args = {val64};
    llvm::Value* val65 = builder.CreateInBoundsGEP(builder.getInt32Ty(), val28, val65_args);
    
    // %66 = load i32, i32* %65, align 4, !tbaa !7
    llvm::Value* val66 = builder.CreateAlignedLoad(builder.getInt32Ty(), val65, llvm::MaybeAlign(4));
    
    // %67 = icmp eq i32 %66, 1
    llvm::Value* val67 = builder.CreateICmpEQ(val66, builder.getInt32(1));
    
    // %68 = zext i1 %67 to i32
    llvm::Value* val68 = builder.CreateZExt(val67, builder.getInt32Ty());
    
    // %69 = add nuw nsw i32 %58, %68
    llvm::Value* val69 = builder.CreateAdd(val58, val68, "", true, true);
    
    // %70 = add nuw nsw i64 %43, 1
    llvm::Value* val70 = builder.CreateAdd(val43, builder.getInt64(1), "", true, true);
    
    // %71 = icmp ult i64 %43, 49
    llvm::Value* val71 = builder.CreateICmpULT(val43, builder.getInt64(49));
    
    // br i1 %71, label %72, label %83
    builder.CreateCondBr(val71, BB72, BB83);
    
    // 72:                                               ; preds = %63
    builder.SetInsertPoint(BB72);
    
    // %73 = add nuw nsw i64 %70, %38
    llvm::Value* val73 = builder.CreateAdd(val70, val38, "", true, true);
    
    // %74 = getelementptr inbounds i32, i32* %28, i64 %73
    llvm::ArrayRef<llvm::Value*> val74_args = {val73};
    llvm::Value* val74 = builder.CreateInBoundsGEP(builder.getInt32Ty(), val28, val74_args);
    
    // %75 = load i32, i32* %74, align 4, !tbaa !7
    llvm::Value* val75 = builder.CreateAlignedLoad(builder.getInt32Ty(), val74, llvm::MaybeAlign(4));
    
    // %76 = icmp eq i32 %75, 1
    llvm::Value* val76 = builder.CreateICmpEQ(val75, builder.getInt32(1));
    
    // %77 = zext i1 %76 to i32
    llvm::Value* val77 = builder.CreateZExt(val76, builder.getInt32Ty());
    
    // %78 = add nuw nsw i32 %69, %77
    llvm::Value* val78 = builder.CreateAdd(val69, val77, "", true, true);
    
    // br label %79
    builder.CreateBr(BB79);
    
    // 79:                                               ; preds = %72, %61, %59
    builder.SetInsertPoint(BB79);
    
    // %80 = phi i64 [ %62, %61 ], [ %70, %72 ], [ %60, %59 ]
    llvm::PHINode* val80 = builder.CreatePHI(builder.getInt64Ty(), 3);
    
    // %81 = phi i32 [ 0, %61 ], [ %78, %72 ], [ %58, %59 ]
    llvm::PHINode* val81 = builder.CreatePHI(builder.getInt32Ty(), 3);
    
    // %82 = icmp eq i64 %43, 0
    llvm::Value* val82 = builder.CreateICmpEQ(val43, builder.getInt64(0));
    
    // br i1 %82, label %94, label %83
    builder.CreateCondBr(val82, BB94, BB83);
    
    // 83:                                               ; preds = %63, %79
    builder.SetInsertPoint(BB83);
    
    // %84 = phi i32 [ %81, %79 ], [ %69, %63 ]
    llvm::PHINode* val84 = builder.CreatePHI(builder.getInt32Ty(), 2);
    
    // %85 = phi i64 [ %80, %79 ], [ %70, %63 ]
    llvm::PHINode* val85 = builder.CreatePHI(builder.getInt64Ty(), 2);
    
    // %86 = add nuw nsw i64 %44, %32
    llvm::Value* val86 = builder.CreateAdd(val44, val32, "", true, true);
    
    // %87 = and i64 %86, 4294967295
    llvm::Value* val87 = builder.CreateAnd(val86, builder.getInt64(4294967295));
    
    // %88 = getelementptr inbounds i32, i32* %28, i64 %87
    llvm::ArrayRef<llvm::Value*> val88_args = {val87};
    llvm::Value* val88 = builder.CreateInBoundsGEP(builder.getInt32Ty(), val28, val88_args);
    
    // %89 = load i32, i32* %88, align 4, !tbaa !7
    llvm::Value* val89 = builder.CreateAlignedLoad(builder.getInt32Ty(), val88, llvm::MaybeAlign(4));
    
    // %90 = icmp eq i32 %89, 1
    llvm::Value* val90 = builder.CreateICmpEQ(val89, builder.getInt32(1));
    
    // %91 = zext i1 %90 to i32
    llvm::Value* val91 = builder.CreateZExt(val90, builder.getInt32Ty());
    
    // %92 = add nuw nsw i32 %84, %91
    llvm::Value* val92 = builder.CreateAdd(val84, val91, "", true, true);
    
    // %93 = icmp ult i64 %43, 49
    llvm::Value* val93 = builder.CreateICmpULT(val43, builder.getInt64(49));
    
    // br i1 %93, label %94, label %103
    builder.CreateCondBr(val93, BB94, BB103);
    
    // 94:                                               ; preds = %83, %79
    builder.SetInsertPoint(BB94);
    
    // %95 = phi i64 [ %85, %83 ], [ %80, %79 ]
    llvm::PHINode* val95 = builder.CreatePHI(builder.getInt64Ty(), 2);
    
    // %96 = phi i32 [ %92, %83 ], [ %81, %79 ]
    llvm::PHINode* val96 = builder.CreatePHI(builder.getInt32Ty(), 2);
    
    // %97 = add nuw nsw i64 %95, %32
    llvm::Value* val97 = builder.CreateAdd(val95, val32, "", true, true);
    
    // %98 = getelementptr inbounds i32, i32* %28, i64 %97
    llvm::ArrayRef<llvm::Value*> val98_args = {val97};
    llvm::Value* val98 = builder.CreateInBoundsGEP(builder.getInt32Ty(), val28, val98_args);
    
    // %99 = load i32, i32* %98, align 4, !tbaa !7
    llvm::Value* val99 = builder.CreateAlignedLoad(builder.getInt32Ty(), val98, llvm::MaybeAlign(4));
    
    // %100 = icmp eq i32 %99, 1
    llvm::Value* val100 = builder.CreateICmpEQ(val99, builder.getInt32(1));
    
    // %101 = zext i1 %100 to i32
    llvm::Value* val101 = builder.CreateZExt(val100, builder.getInt32Ty());
    
    // %102 = add nuw nsw i32 %96, %101
    llvm::Value* val102 = builder.CreateAdd(val96, val101, "", true, true);
    
    // br label %103
    builder.CreateBr(BB103);
    
    // 103:                                              ; preds = %94, %83
    builder.SetInsertPoint(BB103);
    
    // %104 = phi i64 [ %85, %83 ], [ %95, %94 ]
    llvm::PHINode* val104 = builder.CreatePHI(builder.getInt64Ty(), 2);
    
    // %105 = phi i32 [ %92, %83 ], [ %102, %94 ]
    llvm::PHINode* val105 = builder.CreatePHI(builder.getInt32Ty(), 2);
    
    // %106 = icmp ne i64 %43, 0
    llvm::Value* val106 = builder.CreateICmpNE(val43, builder.getInt64(0));
    
    // %107 = select i1 %40, i1 %106, i1 false
    llvm::Value* val107 = builder.CreateSelect(val40, val106, builder.getInt1(false));
    
    // br i1 %107, label %108, label %115
    builder.CreateCondBr(val107, BB108, BB115);
    
    // 108:                                              ; preds = %103
    builder.SetInsertPoint(BB108);
    
    // %109 = add nuw nsw i64 %44, %41
    llvm::Value* val109 = builder.CreateAdd(val44, val41, "", true, true);
    
    // %110 = getelementptr inbounds i32, i32* %28, i64 %109
    llvm::ArrayRef<llvm::Value*> val110_args = {val109};
    llvm::Value* val110 = builder.CreateInBoundsGEP(builder.getInt32Ty(), val28, val110_args);
    
    // %111 = load i32, i32* %110, align 4, !tbaa !7
    llvm::Value* val111 = builder.CreateAlignedLoad(builder.getInt32Ty(), val110, llvm::MaybeAlign(4));
    
    // %112 = icmp eq i32 %111, 1
    llvm::Value* val112 = builder.CreateICmpEQ(val111, builder.getInt32(1));
    
    // %113 = zext i1 %112 to i32
    llvm::Value* val113 = builder.CreateZExt(val112, builder.getInt32Ty());
    
    // %114 = add nuw nsw i32 %105, %113
    llvm::Value* val114 = builder.CreateAdd(val105, val113, "", true, true);
    
    // br label %115
    builder.CreateBr(BB115);
    
    // 115:                                              ; preds = %108, %103
    builder.SetInsertPoint(BB115);
    
    // %116 = phi i32 [ %105, %103 ], [ %114, %108 ]
    llvm::PHINode* val116 = builder.CreatePHI(builder.getInt32Ty(), 2);
    
    // br i1 %40, label %117, label %132
    builder.CreateCondBr(val40, BB117, BB132);
    
    // 117:                                              ; preds = %115
    builder.SetInsertPoint(BB117);
    
    // %118 = add nuw nsw i64 %43, %41
    llvm::Value* val118 = builder.CreateAdd(val43, val41, "", true, true);
    
    // %119 = getelementptr inbounds i32, i32* %28, i64 %118
    llvm::ArrayRef<llvm::Value*> val119_args = {val118};
    llvm::Value* val119 = builder.CreateInBoundsGEP(builder.getInt32Ty(), val28, val119_args);
    
    // %120 = load i32, i32* %119, align 4, !tbaa !7
    llvm::Value* val120 = builder.CreateAlignedLoad(builder.getInt32Ty(), val119, llvm::MaybeAlign(4));
    
    // %121 = icmp eq i32 %120, 1
    llvm::Value* val121 = builder.CreateICmpEQ(val120, builder.getInt32(1));
    
    // %122 = zext i1 %121 to i32
    llvm::Value* val122 = builder.CreateZExt(val121, builder.getInt32Ty());
    
    // %123 = add nuw nsw i32 %116, %122
    llvm::Value* val123 = builder.CreateAdd(val116, val122, "", true, true);
    
    // %124 = icmp ult i64 %43, 49
    llvm::Value* val124 = builder.CreateICmpULT(val43, builder.getInt64(49));
    
    // br i1 %124, label %125, label %132
    builder.CreateCondBr(val124, BB125, BB132);
    
    // 125:                                              ; preds = %117
    builder.SetInsertPoint(BB125);
    
    // %126 = add nuw nsw i64 %104, %41
    llvm::Value* val126 = builder.CreateAdd(val104, val41, "", true, true);
    
    // %127 = getelementptr inbounds i32, i32* %28, i64 %126
    llvm::ArrayRef<llvm::Value*> val127_args = {val126};
    llvm::Value* val127 = builder.CreateInBoundsGEP(builder.getInt32Ty(), val28, val127_args);
    
    // %128 = load i32, i32* %127, align 4, !tbaa !7
    llvm::Value* val128 = builder.CreateAlignedLoad(builder.getInt32Ty(), val127, llvm::MaybeAlign(4));
    
    // %129 = icmp eq i32 %128, 1
    llvm::Value* val129 = builder.CreateICmpEQ(val128, builder.getInt32(1));
    
    // %130 = zext i1 %129 to i32
    llvm::Value* val130 = builder.CreateZExt(val129, builder.getInt32Ty());
    
    // %131 = add nuw nsw i32 %123, %130
    llvm::Value* val131 = builder.CreateAdd(val123, val130, "", true, true);
    
    // br label %132
    builder.CreateBr(BB132);
    
    // 132:                                              ; preds = %125, %117, %115
    builder.SetInsertPoint(BB132);
    
    // %133 = phi i32 [ %123, %117 ], [ %131, %125 ], [ %116, %115 ]
    llvm::PHINode* val133 = builder.CreatePHI(builder.getInt32Ty(), 3);
    
    // %134 = add nuw nsw i64 %43, %32
    llvm::Value* val134 = builder.CreateAdd(val43, val32, "", true, true);
    
    // %135 = getelementptr inbounds i32, i32* %28, i64 %134
    llvm::ArrayRef<llvm::Value*> val135_args = {val134};
    llvm::Value* val135 = builder.CreateInBoundsGEP(builder.getInt32Ty(), val28, val135_args);
    
    // %136 = load i32, i32* %135, align 4, !tbaa !7
    llvm::Value* val136 = builder.CreateAlignedLoad(builder.getInt32Ty(), val135, llvm::MaybeAlign(4));
    
    // %137 = icmp eq i32 %136, 0
    llvm::Value* val137 = builder.CreateICmpEQ(val136, builder.getInt32(0));
    
    // %138 = icmp ne i32 %133, 3
    llvm::Value* val138 = builder.CreateICmpNE(val133, builder.getInt32(3));
    
    // %139 = select i1 %137, i1 %138, i1 false
    llvm::Value* val139 = builder.CreateSelect(val137, val138, builder.getInt1(false));
    
    // br i1 %139, label %145, label %140
    builder.CreateCondBr(val139, BB145, BB140);
    
    // 140:                                              ; preds = %132
    builder.SetInsertPoint(BB140);
    
    // %141 = icmp eq i32 %136, 1
    llvm::Value* val141 = builder.CreateICmpEQ(val136, builder.getInt32(1));
    
    // %142 = icmp ne i32 %133, 2
    llvm::Value* val142 = builder.CreateICmpNE(val133, builder.getInt32(2));
    
    // %143 = select i1 %141, i1 %142, i1 false
    llvm::Value* val143 = builder.CreateSelect(val141, val142, builder.getInt1(false));
    
    // %144 = select i1 %143, i1 %138, i1 false
    llvm::Value* val144 = builder.CreateSelect(val143, val138, builder.getInt1(false));
    
    // br label %145
    builder.CreateBr(BB145);
    
    // 145:                                              ; preds = %140, %132
    builder.SetInsertPoint(BB145);
    
    // %146 = phi i1 [ true, %132 ], [ %144, %140 ]
    llvm::PHINode* val146 = builder.CreatePHI(builder.getInt1Ty(), 2);
    
    // %147 = xor i1 %146, true
    llvm::Value* val147 = builder.CreateXor(val146, builder.getInt1(true));
    
    // %148 = zext i1 %147 to i32
    llvm::Value* val148 = builder.CreateZExt(val147, builder.getInt32Ty());
    
    // %149 = getelementptr inbounds i32, i32* %29, i64 %134
    llvm::ArrayRef<llvm::Value*> val149_args = {val134};
    llvm::Value* val149 = builder.CreateInBoundsGEP(builder.getInt32Ty(), val29, val149_args);
    
    // store i32 %148, i32* %149, align 4, !tbaa !7
    builder.CreateAlignedStore(val148, val149, llvm::MaybeAlign(4));
    
    // %150 = icmp eq i64 %104, 50
    llvm::Value* val150 = builder.CreateICmpEQ(val104, builder.getInt64(50));
    
    // br i1 %150, label %45, label %42, !llvm.loop !12
    builder.CreateCondBr(val150, BB45, BB42);
    
    // 151:                                              ; preds = %45, %155
    builder.SetInsertPoint(BB151);
    
    // %152 = phi i64 [ %156, %155 ], [ 0, %45 ]
    llvm::PHINode* val152 = builder.CreatePHI(builder.getInt64Ty(), 2);
    
    // %153 = mul nuw nsw i64 %152, 50
    llvm::Value* val153 = builder.CreateMul(val152, builder.getInt64(50), "", true, true);
    
    // %154 = trunc i64 %152 to i32
    llvm::Value* val154 = builder.CreateTrunc(val152, builder.getInt32Ty());
    
    // br label %158
    builder.CreateBr(BB158);
    
    // 155:                                              ; preds = %158
    builder.SetInsertPoint(BB155);
    
    // %156 = add nuw nsw i64 %152, 1
    llvm::Value* val156 = builder.CreateAdd(val152, builder.getInt64(1), "", true, true);
    
    // %157 = icmp eq i64 %156, 100
    llvm::Value* val157 = builder.CreateICmpEQ(val156, builder.getInt64(100));
    
    // br i1 %157, label %168, label %151, !llvm.loop !13
    builder.CreateCondBr(val157, BB168, BB151);
    
    // 158:                                              ; preds = %158, %151
    builder.SetInsertPoint(BB158);
    
    // %159 = phi i64 [ 0, %151 ], [ %166, %158 ]
    llvm::PHINode* val159 = builder.CreatePHI(builder.getInt64Ty(), 2);
    
    // %160 = add nuw nsw i64 %159, %153
    llvm::Value* val160 = builder.CreateAdd(val159, val153, "", true, true);
    
    // %161 = getelementptr inbounds i32, i32* %28, i64 %160
    llvm::ArrayRef<llvm::Value*> val161_args = {val160};
    llvm::Value* val161 = builder.CreateInBoundsGEP(builder.getInt32Ty(), val28, val161_args);
    
    // %162 = load i32, i32* %161, align 4, !tbaa !7
    llvm::Value* val162 = builder.CreateAlignedLoad(builder.getInt32Ty(), val161, llvm::MaybeAlign(4));
    
    // %163 = icmp eq i32 %162, 1
    llvm::Value* val163 = builder.CreateICmpEQ(val162, builder.getInt32(1));
    
    // %164 = zext i1 %163 to i32
    llvm::Value* val164 = builder.CreateZExt(val163, builder.getInt32Ty());
    
    // %165 = trunc i64 %159 to i32
    llvm::Value* val165 = builder.CreateTrunc(val159, builder.getInt32Ty());
    
    // tail call void @sim_set_pixel(i32 noundef %154, i32 noundef %165, i32 noundef %164) #3
    
    // %166 = add nuw nsw i64 %159, 1
    llvm::Value* val166 = builder.CreateAdd(val159, builder.getInt64(1), "", true, true);
    
    // %167 = icmp eq i64 %166, 50
    llvm::Value* val167 = builder.CreateICmpEQ(val166, builder.getInt64(50));
    
    // br i1 %167, label %155, label %158, !llvm.loop !14
    builder.CreateCondBr(val167, BB155, BB158);
    
    // 168:                                              ; preds = %155
    builder.SetInsertPoint(BB168);
    
    // tail call void @sim_flush() #3
    builder.CreateCall(sim_flush_func)->setTailCall(true);
    
    // %169 = tail call i32 @sim_keep_running() #3
    llvm::CallInst* val169 = builder.CreateCall(sim_keep_running_func);
    val169->setTailCall(true);
    
    // %170 = icmp eq i32 %169, 0
    llvm::Value* val170 = builder.CreateICmpEQ(val169, builder.getInt32(0));
    
    // br i1 %170, label %171, label %27, !llvm.loop !15
    builder.CreateCondBr(val170, BB171, BB27);
    
    // 171:                                              ; preds = %168, %12
    builder.SetInsertPoint(BB171);
    
    // call void @llvm.lifetime.end.p0i8(i64 20000, i8* nonnull %4) #3
    builder.CreateCall(llvm_lifetime_end_p0i8_func, llvm::ArrayRef<llvm::Value*> {builder.getInt64(20000), val4})->setTailCall(false);
    
    // call void @llvm.lifetime.end.p0i8(i64 20000, i8* nonnull %3) #3
    builder.CreateCall(llvm_lifetime_end_p0i8_func, llvm::ArrayRef<llvm::Value*> {builder.getInt64(20000), val3})->setTailCall(false);
    
    // ret void
    builder.CreateRetVoid();
    
    // }
    
    // ; Function Attrs: argmemonly mustprogress nofree nosync nounwind willreturn
    
    // declare void @llvm.lifetime.start.p0i8(i64 immarg, i8* nocapture) #1
    
    // declare i32 @sim_keep_running() local_unnamed_addr #2
    
    // ; Function Attrs: argmemonly mustprogress nofree nosync nounwind willreturn
    
    // declare void @llvm.lifetime.end.p0i8(i64 immarg, i8* nocapture) #1
    
    // declare i32 @sim_rand() local_unnamed_addr #2
    
    // declare void @sim_set_pixel(i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #2
    
    // declare void @sim_flush() local_unnamed_addr #2
    
    // attributes #0 = { nounwind uwtable "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
    
    // attributes #1 = { argmemonly mustprogress nofree nosync nounwind willreturn }
    
    // attributes #2 = { "frame-pointer"="none" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
    
    // attributes #3 = { nounwind }
    
    // !llvm.module.flags = !{!0, !1, !2, !3}
    
    // !llvm.ident = !{!4}
    
    // !0 = !{i32 1, !"wchar_size", i32 4}
    
    // !1 = !{i32 7, !"PIC Level", i32 2}
    
    // !2 = !{i32 7, !"PIE Level", i32 2}
    
    // !3 = !{i32 7, !"uwtable", i32 1}
    
    // !4 = !{!"Ubuntu clang version 14.0.0-1ubuntu1.1"}
    
    // !5 = distinct !{!5, !6}
    
    // !6 = !{!"llvm.loop.mustprogress"}
    
    // !7 = !{!8, !8, i64 0}
    
    // !8 = !{!"omnipotent char", !9, i64 0}
    
    // !9 = !{!"Simple C/C++ TBAA"}
    
    // !10 = distinct !{!10, !6}
    
    // !11 = distinct !{!11, !6}
    
    // !12 = distinct !{!12, !6}
    
    // !13 = distinct !{!13, !6}
    
    // !14 = distinct !{!14, !6}
    
    // !15 = distinct !{!15, !6}
    
    val7->addIncoming(builder.getInt64(0), BB0);
    val7->addIncoming(val10, BB9);
    val18->addIncoming(builder.getInt64(0), BB6);
    val18->addIncoming(val25, BB17);
    val28->addIncoming(val29, BB168);
    val28->addIncoming(val5, BB15);
    val29->addIncoming(val28, BB168);
    val29->addIncoming(val16, BB15);
    val31->addIncoming(val39, BB45);
    val31->addIncoming(builder.getInt64(0), BB27);
    val43->addIncoming(builder.getInt64(0), BB30);
    val43->addIncoming(val104, BB145);
    val58->addIncoming(val56, BB50);
    val58->addIncoming(builder.getInt32(0), BB47);
    val80->addIncoming(val62, BB61);
    val80->addIncoming(val70, BB72);
    val80->addIncoming(val60, BB59);
    val81->addIncoming(builder.getInt32(0), BB61);
    val81->addIncoming(val78, BB72);
    val81->addIncoming(val58, BB59);
    val84->addIncoming(val81, BB79);
    val84->addIncoming(val69, BB63);
    val85->addIncoming(val80, BB79);
    val85->addIncoming(val70, BB63);
    val95->addIncoming(val85, BB83);
    val95->addIncoming(val80, BB79);
    val96->addIncoming(val92, BB83);
    val96->addIncoming(val81, BB79);
    val104->addIncoming(val85, BB83);
    val104->addIncoming(val95, BB94);
    val105->addIncoming(val92, BB83);
    val105->addIncoming(val102, BB94);
    val116->addIncoming(val105, BB103);
    val116->addIncoming(val114, BB108);
    val133->addIncoming(val123, BB117);
    val133->addIncoming(val131, BB125);
    val133->addIncoming(val116, BB115);
    val146->addIncoming(builder.getInt1(true), BB132);
    val146->addIncoming(val144, BB140);
    val152->addIncoming(val156, BB155);
    val152->addIncoming(builder.getInt64(0), BB45);
    val159->addIncoming(builder.getInt64(0), BB151);
    val159->addIncoming(val166, BB158);
    
    std::error_code ec{};
    llvm::raw_fd_ostream out(argv[1], ec);
    module->print(out, nullptr);
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::ExecutionEngine *ee = llvm::EngineBuilder(std::unique_ptr<llvm::Module>(module)).create();
    ee->InstallLazyFunctionCreator([&](const std::string &fnName) -> void * {
        if (fnName == "sim_keep_running") {
            return reinterpret_cast<void *>(sim_keep_running);
        } else if (fnName == "sim_set_pixel") {
            return reinterpret_cast<void *>(sim_set_pixel);
        } else if (fnName == "sim_flush") {
            return reinterpret_cast<void *>(sim_flush);
        } else if (fnName == "sim_rand") {
            return reinterpret_cast<void *>(sim_rand);
            } else {
            return nullptr;
        }
    });
    ee->finalizeObject();
    
    llvm::ArrayRef<llvm::GenericValue> noargs;
    llvm::GenericValue v = ee->runFunction(app_func, noargs);
}
