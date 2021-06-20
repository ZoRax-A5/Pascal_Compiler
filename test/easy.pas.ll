; ModuleID = 'pascal_module'
source_filename = "pascal_module"

@aa = common constant i32 5
@bb = common constant i8 99
@cc = common constant double 3.200000e+00
@a = common global i32 0
@b = common global i32 0
@c = common global double 0.000000e+00
@d = common global double 0.000000e+00
@n = common global i32 0
@is_small = common global i1 false
@char_mine = common global i8 0
@scanf_format = private unnamed_addr constant [9 x i8] c"%d%*[^\0A]\00", align 1
@scanf_newline = private unnamed_addr constant [4 x i8] c"%*c\00", align 1
@printf_format = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@printf_format.1 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@printf_format.2 = private unnamed_addr constant [5 x i8] c"%lf\0A\00", align 1
@printf_format.3 = private unnamed_addr constant [4 x i8] c"%c\0A\00", align 1
@printf_format.4 = private unnamed_addr constant [5 x i8] c"%lf\0A\00", align 1
@printf_format.5 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

define i32 @main() {
entry:
  store i32 5, i32* @aa
  store i8 99, i8* @bb
  store double 3.200000e+00, double* @cc
  %0 = load double, double* @c
  store double 3.200000e+00, double* @c
  %1 = load i32, i32* @a
  store i32 5, i32* @a
  %2 = load i32, i32* @b
  store i32 6, i32* @b
  %3 = load double, double* @d
  store double 3.200000e+00, double* @d
  %4 = load i32, i32* @n
  %call_scanf = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @scanf_format, i32 0, i32 0), i32* @n)
  %call_scanf1 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @scanf_newline, i32 0, i32 0))
  %5 = load i32, i32* @a
  %6 = load i32, i32* @n
  %7 = call i1 @Compare(i32* @a, i32* @n)
  br i1 %7, label %if_then, label %if_else

if_then:                                          ; preds = %entry
  %8 = load i32, i32* @a
  %call_printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format, i32 0, i32 0), i32 %8)
  br label %if_cont

if_else:                                          ; preds = %entry
  %9 = load i32, i32* @n
  %call_printf2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format.1, i32 0, i32 0), i32 %9)
  br label %if_cont

if_cont:                                          ; preds = %if_else, %if_then
  %10 = load i8, i8* @char_mine
  %11 = load i8, i8* @bb
  store i8 %11, i8* @char_mine
  %12 = load double, double* @d
  %13 = load double, double* @d
  %14 = load i32, i32* @aa
  %15 = uitofp i32 %14 to double
  %addftmp = fadd double %13, %15
  store double %addftmp, double* @d
  %16 = load double, double* @d
  %call_printf3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @printf_format.2, i32 0, i32 0), double %16)
  %17 = load i32, i32* @aa
  %18 = load i32, i32* @a
  %19 = call i1 @Is_equal(i32* @aa, i32* @a)
  br i1 %19, label %if_then4, label %if_else5

if_then4:                                         ; preds = %if_cont
  %20 = load i8, i8* @bb
  %call_printf7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format.3, i32 0, i32 0), i8 %20)
  br label %if_cont6

if_else5:                                         ; preds = %if_cont
  %21 = load double, double* @cc
  %call_printf8 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @printf_format.4, i32 0, i32 0), double %21)
  br label %if_cont6

if_cont6:                                         ; preds = %if_else5, %if_then4
  br label %repeat_body

repeat_body:                                      ; preds = %repeat_cond, %if_cont6
  %22 = load i32, i32* @b
  %23 = load i32, i32* @b
  %addtmp = add i32 %23, 1
  store i32 %addtmp, i32* @b
  br label %repeat_cond

repeat_cond:                                      ; preds = %repeat_body
  %24 = load i32, i32* @b
  %cmptmp = icmp eq i32 %24, 19
  br i1 %cmptmp, label %repeat_cont, label %repeat_body

repeat_cont:                                      ; preds = %repeat_cond
  br label %while_cond

while_cond:                                       ; preds = %while_body, %repeat_cont
  %25 = load i32, i32* @n
  %26 = load i32, i32* @b
  %27 = call i1 @Compare(i32* @n, i32* @b)
  br i1 %27, label %while_body, label %while_end

while_body:                                       ; preds = %while_cond
  %28 = load i32, i32* @n
  %29 = load i32, i32* @n
  %addtmp9 = add i32 %29, 1
  store i32 %addtmp9, i32* @n
  br label %while_cond

while_end:                                        ; preds = %while_cond
  %30 = load i32, i32* @n
  %call_printf10 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format.5, i32 0, i32 0), i32 %30)
  %31 = load i1, i1* @is_small
  %32 = load i32, i32* @a
  %33 = load i32, i32* @aa
  %34 = call i1 @Compare(i32* @a, i32* @aa)
  store i1 %34, i1* @is_small
  ret i32 0
}

define i1 @Compare(i32* %0, i32* %1) {
entry:
  %2 = load i32, i32* %0
  %x = alloca i32
  store i32 %2, i32* %x
  %3 = load i32, i32* %1
  %y = alloca i32
  store i32 %3, i32* %y
  %Compare = alloca i1
  %4 = load i32, i32* %x
  %5 = load i32, i32* %y
  %cmptmp = icmp slt i32 %4, %5
  br i1 %cmptmp, label %if_then, label %if_else

if_then:                                          ; preds = %entry
  %6 = load i1, i1* %Compare
  store i1 true, i1* %Compare
  br label %if_cont

if_else:                                          ; preds = %entry
  %7 = load i1, i1* %Compare
  store i1 false, i1* %Compare
  br label %if_cont

if_cont:                                          ; preds = %if_else, %if_then
  %8 = load i1, i1* %Compare
  ret i1 %8
}

define i1 @Is_equal(i32* %0, i32* %1) {
entry:
  %2 = load i32, i32* %0
  %x = alloca i32
  store i32 %2, i32* %x
  %3 = load i32, i32* %1
  %y = alloca i32
  store i32 %3, i32* %y
  %Is_equal = alloca i1
  %4 = load i32, i32* %x
  %5 = load i32, i32* %y
  %cmptmp = icmp eq i32 %4, %5
  br i1 %cmptmp, label %if_then, label %if_else

if_then:                                          ; preds = %entry
  %6 = load i1, i1* %Is_equal
  store i1 true, i1* %Is_equal
  br label %if_cont

if_else:                                          ; preds = %entry
  %7 = load i1, i1* %Is_equal
  store i1 false, i1* %Is_equal
  br label %if_cont

if_cont:                                          ; preds = %if_else, %if_then
  %8 = load i1, i1* %Is_equal
  ret i1 %8
}

declare i32 @scanf(i8*, ...)

declare i32 @printf(i8*, ...)
