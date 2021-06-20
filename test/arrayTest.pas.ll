; ModuleID = 'pascal_module'
source_filename = "pascal_module"

@r = common global i32 0
@i = common global i32 0
@n = common global i32 0
@sum = common global i32 0
@scanf_format = private unnamed_addr constant [9 x i8] c"%d%*[^\0A]\00"
@scanf_newline = private unnamed_addr constant [4 x i8] c"%*c\00"
@scanf_format.1 = private unnamed_addr constant [3 x i8] c"%d\00"
@printf_format = private unnamed_addr constant [4 x i8] c"%d\0A\00"
@printf_format.2 = private unnamed_addr constant [4 x i8] c"%d\0A\00"

define i32 @main() {
entry:
  %0 = load i32, i32* @n
  %call_scanf = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @scanf_format, i32 0, i32 0), i32* @n)
  %call_scanf1 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @scanf_newline, i32 0, i32 0))
  %1 = load i32, i32* @i
  store i32 1, i32* @i
  br label %repeat_body

repeat_body:                                      ; preds = %repeat_cond, %entry
  %2 = load i32, i32* @i
  %3 = load i32, i32* @r
  %call_scanf2 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @scanf_format.1, i32 0, i32 0), i32* @r)
  %4 = load i32, i32* @i
  %call_printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format, i32 0, i32 0), i32 %4)
  %5 = load i32, i32* @i
  %6 = load i32, i32* @i
  %addtmp = add i32 %6, 1
  store i32 %addtmp, i32* @i
  br label %repeat_cond

repeat_cond:                                      ; preds = %repeat_body
  %7 = load i32, i32* @i
  %8 = load i32, i32* @n
  %addtmp3 = add i32 %8, 1
  %cmptmp = icmp eq i32 %7, %addtmp3
  br i1 %cmptmp, label %repeat_cont, label %repeat_body

repeat_cont:                                      ; preds = %repeat_cond
  %9 = load i32, i32* @sum
  store i32 0, i32* @sum
  %10 = load i32, i32* @i
  store i32 1, i32* @i
  br label %repeat_body4

repeat_body4:                                     ; preds = %repeat_cond5, %repeat_cont
  %11 = load i32, i32* @sum
  %12 = load i32, i32* @sum
  %13 = load i32, i32* @i
  %14 = load i32, i32* @r
  %addtmp7 = add i32 %12, %14
  store i32 %addtmp7, i32* @sum
  %15 = load i32, i32* @i
  %16 = load i32, i32* @i
  %addtmp8 = add i32 %16, 1
  store i32 %addtmp8, i32* @i
  br label %repeat_cond5

repeat_cond5:                                     ; preds = %repeat_body4
  %17 = load i32, i32* @i
  %18 = load i32, i32* @n
  %addtmp9 = add i32 %18, 1
  %cmptmp10 = icmp eq i32 %17, %addtmp9
  br i1 %cmptmp10, label %repeat_cont6, label %repeat_body4

repeat_cont6:                                     ; preds = %repeat_cond5
  %19 = load i32, i32* @sum
  %call_printf11 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format.2, i32 0, i32 0), i32 %19)
  ret i32 0
}

declare i32 @scanf(i8*, ...)

declare i32 @printf(i8*, ...)
