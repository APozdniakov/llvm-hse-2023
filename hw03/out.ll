; ModuleID = '/home/alexey/opt/llvm-hse-2023/hw01/life.c'
source_filename = "/home/alexey/opt/llvm-hse-2023/hw01/life.c"

define void @app() {
  %1 = alloca [5000 x i32], align 16
  %2 = alloca [5000 x i32], align 16
  %3 = bitcast [5000 x i32]* %1 to i8*
  call void @llvm.lifetime.start.p0i8(i64 20000, i8* %3)
  %4 = bitcast [5000 x i32]* %2 to i8*
  call void @llvm.lifetime.start.p0i8(i64 20000, i8* %4)
  %5 = getelementptr inbounds [5000 x i32], [5000 x i32]* %1, i64 0, i64 0
  br label %6

6:                                                ; preds = %9, %0
  %7 = phi i64 [ 0, %0 ], [ %10, %9 ]
  %8 = mul nuw nsw i64 %7, 50
  br label %17

9:                                                ; preds = %17
  %10 = add nuw nsw i64 %7, 1
  %11 = icmp eq i64 %10, 100
  br i1 %11, label %12, label %6

12:                                               ; preds = %9
  %13 = tail call i32 @sim_keep_running()
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %171, label %15

15:                                               ; preds = %12
  %16 = getelementptr inbounds [5000 x i32], [5000 x i32]* %2, i64 0, i64 0
  br label %27

17:                                               ; preds = %17, %6
  %18 = phi i64 [ 0, %6 ], [ %25, %17 ]
  %19 = tail call i32 @sim_rand()
  %20 = and i32 %19, 3
  %21 = icmp eq i32 %20, 0
  %22 = zext i1 %21 to i32
  %23 = add nuw nsw i64 %18, %8
  %24 = getelementptr inbounds [5000 x i32], [5000 x i32]* %1, i64 0, i64 %23
  store i32 %22, i32* %24, align 4
  %25 = add nuw nsw i64 %18, 1
  %26 = icmp eq i64 %25, 50
  br i1 %26, label %9, label %17

27:                                               ; preds = %168, %15
  %28 = phi i32* [ %29, %168 ], [ %5, %15 ]
  %29 = phi i32* [ %28, %168 ], [ %16, %15 ]
  br label %30

30:                                               ; preds = %45, %27
  %31 = phi i64 [ %39, %45 ], [ 0, %27 ]
  %32 = mul nuw nsw i64 %31, 50
  %33 = add nsw i64 %31, -1
  %34 = icmp eq i64 %31, 0
  %35 = trunc i64 %33 to i32
  %36 = icmp ult i32 %35, 100
  %37 = mul nuw nsw i64 %33, 50
  %38 = and i64 %37, 4294967294
  %39 = add nuw nsw i64 %31, 1
  %40 = icmp ult i64 %31, 99
  %41 = mul nuw nsw i64 %39, 50
  br label %42

42:                                               ; preds = %145, %30
  %43 = phi i64 [ 0, %30 ], [ %104, %145 ]
  %44 = add nsw i64 %43, -1
  br i1 %34, label %61, label %47

45:                                               ; preds = %145
  %46 = icmp eq i64 %39, 100
  br i1 %46, label %151, label %30

47:                                               ; preds = %42
  %48 = icmp ne i64 %43, 0
  %49 = select i1 %36, i1 %48, i1 false
  br i1 %49, label %50, label %57

50:                                               ; preds = %47
  %51 = add nuw nsw i64 %44, %37
  %52 = and i64 %51, 4294967295
  %53 = getelementptr inbounds i32, i32* %28, i64 %52
  %54 = load i32, i32* %53, align 4
  %55 = icmp eq i32 %54, 1
  %56 = zext i1 %55 to i32
  br label %57

57:                                               ; preds = %50, %47
  %58 = phi i32 [ %56, %50 ], [ 0, %47 ]
  br i1 %36, label %63, label %59

59:                                               ; preds = %57
  %60 = add nuw nsw i64 %43, 1
  br label %79

61:                                               ; preds = %42
  %62 = add nuw nsw i64 %43, 1
  br label %79

63:                                               ; preds = %57
  %64 = add nuw nsw i64 %43, %38
  %65 = getelementptr inbounds i32, i32* %28, i64 %64
  %66 = load i32, i32* %65, align 4
  %67 = icmp eq i32 %66, 1
  %68 = zext i1 %67 to i32
  %69 = add nuw nsw i32 %58, %68
  %70 = add nuw nsw i64 %43, 1
  %71 = icmp ult i64 %43, 49
  br i1 %71, label %72, label %83

72:                                               ; preds = %63
  %73 = add nuw nsw i64 %70, %38
  %74 = getelementptr inbounds i32, i32* %28, i64 %73
  %75 = load i32, i32* %74, align 4
  %76 = icmp eq i32 %75, 1
  %77 = zext i1 %76 to i32
  %78 = add nuw nsw i32 %69, %77
  br label %79

79:                                               ; preds = %72, %61, %59
  %80 = phi i64 [ %62, %61 ], [ %70, %72 ], [ %60, %59 ]
  %81 = phi i32 [ 0, %61 ], [ %78, %72 ], [ %58, %59 ]
  %82 = icmp eq i64 %43, 0
  br i1 %82, label %94, label %83

83:                                               ; preds = %79, %63
  %84 = phi i32 [ %81, %79 ], [ %69, %63 ]
  %85 = phi i64 [ %80, %79 ], [ %70, %63 ]
  %86 = add nuw nsw i64 %44, %32
  %87 = and i64 %86, 4294967295
  %88 = getelementptr inbounds i32, i32* %28, i64 %87
  %89 = load i32, i32* %88, align 4
  %90 = icmp eq i32 %89, 1
  %91 = zext i1 %90 to i32
  %92 = add nuw nsw i32 %84, %91
  %93 = icmp ult i64 %43, 49
  br i1 %93, label %94, label %103

94:                                               ; preds = %83, %79
  %95 = phi i64 [ %85, %83 ], [ %80, %79 ]
  %96 = phi i32 [ %92, %83 ], [ %81, %79 ]
  %97 = add nuw nsw i64 %95, %32
  %98 = getelementptr inbounds i32, i32* %28, i64 %97
  %99 = load i32, i32* %98, align 4
  %100 = icmp eq i32 %99, 1
  %101 = zext i1 %100 to i32
  %102 = add nuw nsw i32 %96, %101
  br label %103

103:                                              ; preds = %94, %83
  %104 = phi i64 [ %85, %83 ], [ %95, %94 ]
  %105 = phi i32 [ %92, %83 ], [ %102, %94 ]
  %106 = icmp ne i64 %43, 0
  %107 = select i1 %40, i1 %106, i1 false
  br i1 %107, label %108, label %115

108:                                              ; preds = %103
  %109 = add nuw nsw i64 %44, %41
  %110 = getelementptr inbounds i32, i32* %28, i64 %109
  %111 = load i32, i32* %110, align 4
  %112 = icmp eq i32 %111, 1
  %113 = zext i1 %112 to i32
  %114 = add nuw nsw i32 %105, %113
  br label %115

115:                                              ; preds = %108, %103
  %116 = phi i32 [ %105, %103 ], [ %114, %108 ]
  br i1 %40, label %117, label %132

117:                                              ; preds = %115
  %118 = add nuw nsw i64 %43, %41
  %119 = getelementptr inbounds i32, i32* %28, i64 %118
  %120 = load i32, i32* %119, align 4
  %121 = icmp eq i32 %120, 1
  %122 = zext i1 %121 to i32
  %123 = add nuw nsw i32 %116, %122
  %124 = icmp ult i64 %43, 49
  br i1 %124, label %125, label %132

125:                                              ; preds = %117
  %126 = add nuw nsw i64 %104, %41
  %127 = getelementptr inbounds i32, i32* %28, i64 %126
  %128 = load i32, i32* %127, align 4
  %129 = icmp eq i32 %128, 1
  %130 = zext i1 %129 to i32
  %131 = add nuw nsw i32 %123, %130
  br label %132

132:                                              ; preds = %125, %117, %115
  %133 = phi i32 [ %123, %117 ], [ %131, %125 ], [ %116, %115 ]
  %134 = add nuw nsw i64 %43, %32
  %135 = getelementptr inbounds i32, i32* %28, i64 %134
  %136 = load i32, i32* %135, align 4
  %137 = icmp eq i32 %136, 0
  %138 = icmp ne i32 %133, 3
  %139 = select i1 %137, i1 %138, i1 false
  br i1 %139, label %145, label %140

140:                                              ; preds = %132
  %141 = icmp eq i32 %136, 1
  %142 = icmp ne i32 %133, 2
  %143 = select i1 %141, i1 %142, i1 false
  %144 = select i1 %143, i1 %138, i1 false
  br label %145

145:                                              ; preds = %140, %132
  %146 = phi i1 [ true, %132 ], [ %144, %140 ]
  %147 = xor i1 %146, true
  %148 = zext i1 %147 to i32
  %149 = getelementptr inbounds i32, i32* %29, i64 %134
  store i32 %148, i32* %149, align 4
  %150 = icmp eq i64 %104, 50
  br i1 %150, label %45, label %42

151:                                              ; preds = %155, %45
  %152 = phi i64 [ %156, %155 ], [ 0, %45 ]
  %153 = mul nuw nsw i64 %152, 50
  %154 = trunc i64 %152 to i32
  br label %158

155:                                              ; preds = %158
  %156 = add nuw nsw i64 %152, 1
  %157 = icmp eq i64 %156, 100
  br i1 %157, label %168, label %151

158:                                              ; preds = %158, %151
  %159 = phi i64 [ 0, %151 ], [ %166, %158 ]
  %160 = add nuw nsw i64 %159, %153
  %161 = getelementptr inbounds i32, i32* %28, i64 %160
  %162 = load i32, i32* %161, align 4
  %163 = icmp eq i32 %162, 1
  %164 = zext i1 %163 to i32
  %165 = trunc i64 %159 to i32
  %166 = add nuw nsw i64 %159, 1
  %167 = icmp eq i64 %166, 50
  br i1 %167, label %155, label %158

168:                                              ; preds = %155
  tail call void @sim_flush()
  %169 = tail call i32 @sim_keep_running()
  %170 = icmp eq i32 %169, 0
  br i1 %170, label %171, label %27

171:                                              ; preds = %168, %12
  call void @llvm.lifetime.end.p0i8(i64 20000, i8* %4)
  call void @llvm.lifetime.end.p0i8(i64 20000, i8* %3)
  ret void
}

; Function Attrs: argmemonly nofree nosync nounwind willreturn
declare void @llvm.lifetime.start.p0i8(i64 immarg, i8* nocapture) #0

declare i32 @sim_keep_running()

; Function Attrs: argmemonly nofree nosync nounwind willreturn
declare void @llvm.lifetime.end.p0i8(i64 immarg, i8* nocapture) #0

declare i32 @sim_rand()

declare void @sim_set_pixel(i32, i32, i32)

declare void @sim_flush()

attributes #0 = { argmemonly nofree nosync nounwind willreturn }
