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
@str = common global [256 x i8] zeroinitializer
@0 = private unnamed_addr constant [256 x i8] c"Hello World!\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00", align 1
@scanf_format = private unnamed_addr constant [9 x i8] c"%d%*[^\0A]\00", align 1
@scanf_newline = private unnamed_addr constant [4 x i8] c"%*c\00", align 1
@printf_format = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@printf_format.1 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@printf_format.2 = private unnamed_addr constant [5 x i8] c"%lf\0A\00", align 1
@printf_format.3 = private unnamed_addr constant [4 x i8] c"%c\0A\00", align 1
@printf_format.4 = private unnamed_addr constant [5 x i8] c"%lf\0A\00", align 1
@printf_format.5 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@printf_format.6 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

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
  %4 = load [256 x i8], [256 x i8]* @str
  %5 = load [256 x i8], [256 x i8]* @0
  store [256 x i8] %5, [256 x i8]* @str
  %6 = load i32, i32* @n
  %call_scanf = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @scanf_format, i32 0, i32 0), i32* @n)
  %call_scanf1 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @scanf_newline, i32 0, i32 0))
  %7 = load i32, i32* @a
  %8 = load i32, i32* @n
  %9 = call i1 @Compare(i32* @a, i32* @n)
  br i1 %9, label %if_then, label %if_else

if_then:                                          ; preds = %entry
  %10 = load i32, i32* @a
  %call_printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format, i32 0, i32 0), i32 %10)
  br label %if_cont

if_else:                                          ; preds = %entry
  %11 = load i32, i32* @n
  %call_printf2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format.1, i32 0, i32 0), i32 %11)
  br label %if_cont

if_cont:                                          ; preds = %if_else, %if_then
  %12 = load i8, i8* @char_mine
  %13 = load i8, i8* @bb
  store i8 %13, i8* @char_mine
  %14 = load double, double* @d
  %15 = load double, double* @d
  %16 = load i32, i32* @aa
  %17 = uitofp i32 %16 to double
  %addftmp = fadd double %15, %17
  store double %addftmp, double* @d
  %18 = load double, double* @d
  %call_printf3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @printf_format.2, i32 0, i32 0), double %18)
  %19 = load i32, i32* @aa
  %20 = load i32, i32* @a
  %21 = call i1 @Is_equal(i32* @aa, i32* @a)
  br i1 %21, label %if_then4, label %if_else5

if_then4:                                         ; preds = %if_cont
  %22 = load i8, i8* @bb
  %call_printf7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format.3, i32 0, i32 0), i8 %22)
  br label %if_cont6

if_else5:                                         ; preds = %if_cont
  %23 = load double, double* @cc
  %call_printf8 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @printf_format.4, i32 0, i32 0), double %23)
  br label %if_cont6

if_cont6:                                         ; preds = %if_else5, %if_then4
  %24 = load [256 x i8], [256 x i8]* @str
  %call_printf9 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format.5, i32 0, i32 0), [256 x i8]* @str)
  br label %repeat_body

repeat_body:                                      ; preds = %repeat_cond, %if_cont6
  %25 = load i32, i32* @b
  %26 = load i32, i32* @b
  %addtmp = add i32 %26, 1
  store i32 %addtmp, i32* @b
  br label %repeat_cond

repeat_cond:                                      ; preds = %repeat_body
  %27 = load i32, i32* @b
  %cmptmp = icmp eq i32 %27, 19
  br i1 %cmptmp, label %repeat_cont, label %repeat_body

repeat_cont:                                      ; preds = %repeat_cond
  br label %while_cond

while_cond:                                       ; preds = %while_body, %repeat_cont
  %28 = load i32, i32* @n
  %29 = load i32, i32* @b
  %30 = call i1 @Compare(i32* @n, i32* @b)
  br i1 %30, label %while_body, label %while_end

while_body:                                       ; preds = %while_cond
  %31 = load i32, i32* @n
  %32 = load i32, i32* @n
  %addtmp10 = add i32 %32, 1
  store i32 %addtmp10, i32* @n
  br label %while_cond

while_end:                                        ; preds = %while_cond
  %33 = load i32, i32* @n
  %call_printf11 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format.6, i32 0, i32 0), i32 %33)
  %34 = load i1, i1* @is_small
  %35 = load i32, i32* @a
  %36 = load i32, i32* @aa
  %37 = call i1 @Compare(i32* @a, i32* @aa)
  store i1 %37, i1* @is_small
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
