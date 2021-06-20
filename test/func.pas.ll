; ModuleID = 'pascal_module'
source_filename = "pascal_module"

@a = common global i32 0
@b = common global i32 0
@c = common global i32 0
@min = common global i32 0
@printf_format = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@printf_format.1 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

define i32 @main() {
entry:
  %0 = load i32, i32* @a
  store i32 1, i32* @a
  %1 = load i32, i32* @b
  store i32 2, i32* @b
  %2 = load i32, i32* @c
  store i32 3, i32* @c
  %3 = load i32, i32* @min
  store i32 4, i32* @min
  %4 = load i32, i32* @a
  %5 = load i32, i32* @b
  %6 = load i32, i32* @c
  %7 = load i32, i32* @min
  call void @findMin(i32* @a, i32* @b, i32* @c, i32* @min)
  %8 = load i32, i32* @min
  %call_printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format.1, i32 0, i32 0), i32 %8)
  ret i32 0
}

define void @findMin(i32* %0, i32* %1, i32* %2, i32* %3) {
entry:
  %4 = load i32, i32* %0
  %x = alloca i32
  store i32 %4, i32* %x
  %5 = load i32, i32* %1
  %y = alloca i32
  store i32 %5, i32* %y
  %6 = load i32, i32* %2
  %z = alloca i32
  store i32 %6, i32* %z
  %7 = load i32, i32* %x
  %8 = load i32, i32* %y
  %cmptmp = icmp slt i32 %7, %8
  br i1 %cmptmp, label %if_then, label %if_else

if_then:                                          ; preds = %entry
  %9 = load i32, i32* %3
  %10 = load i32, i32* %x
  store i32 %10, i32* %3
  br label %if_cont

if_else:                                          ; preds = %entry
  %11 = load i32, i32* %3
  %12 = load i32, i32* %y
  store i32 %12, i32* %3
  br label %if_cont

if_cont:                                          ; preds = %if_else, %if_then
  %13 = load i32, i32* %z
  %14 = load i32, i32* %3
  %cmptmp4 = icmp slt i32 %13, %14
  br i1 %cmptmp4, label %if_then1, label %if_else2

if_then1:                                         ; preds = %if_cont
  %15 = load i32, i32* %3
  %16 = load i32, i32* %z
  store i32 %16, i32* %3
  br label %if_cont3

if_else2:                                         ; preds = %if_cont
  br label %if_cont3

if_cont3:                                         ; preds = %if_else2, %if_then1
  %17 = load i32, i32* %3
  %call_printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format, i32 0, i32 0), i32 %17)
  ret void
}

declare i32 @printf(i8*, ...)

define i32 @max(i32* %0, i32* %1) {
entry:
  %2 = load i32, i32* %0
  %num1 = alloca i32
  store i32 %2, i32* %num1
  %3 = load i32, i32* %1
  %num2 = alloca i32
  store i32 %3, i32* %num2
  %max = alloca i32
  %result = alloca i32
  %4 = load i32, i32* %num1
  %5 = load i32, i32* %num2
  %cmptmp = icmp sgt i32 %4, %5
  br i1 %cmptmp, label %if_then, label %if_else

if_then:                                          ; preds = %entry
  %6 = load i32, i32* %result
  %7 = load i32, i32* %num1
  store i32 %7, i32* %result
  br label %if_cont

if_else:                                          ; preds = %entry
  %8 = load i32, i32* %result
  %9 = load i32, i32* %num2
  store i32 %9, i32* %result
  br label %if_cont

if_cont:                                          ; preds = %if_else, %if_then
  %10 = load i32, i32* %max
  %11 = load i32, i32* %result
  store i32 %11, i32* %max
  %12 = load i32, i32* %max
  ret i32 %12
}
