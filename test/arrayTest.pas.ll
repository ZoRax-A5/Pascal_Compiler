; ModuleID = 'pascal_module'
source_filename = "pascal_module"

@r = common global [100 x i32] zeroinitializer
@i = common global i32 0
@n = common global i32 0
@sum = common global i32 0
@scanf_format = private unnamed_addr constant [9 x i8] c"%d%*[^\0A]\00", align 1
@scanf_newline = private unnamed_addr constant [4 x i8] c"%*c\00", align 1
@scanf_format.1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@printf_format = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@printf_format.2 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

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
  %3 = load [100 x i32], [100 x i32]* @r
  %subtmp = sub i32 %2, 1
  %ArrayCall = getelementptr [100 x i32], [100 x i32]* @r, i32 0, i32 %subtmp
  %4 = load i32, i32* %ArrayCall
  %call_scanf2 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @scanf_format.1, i32 0, i32 0), i32* %ArrayCall)
  %5 = load i32, i32* @i
  %call_printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format, i32 0, i32 0), i32 %5)
  %6 = load i32, i32* @i
  %7 = load i32, i32* @i
  %addtmp = add i32 %7, 1
  store i32 %addtmp, i32* @i
  br label %repeat_cond

repeat_cond:                                      ; preds = %repeat_body
  %8 = load i32, i32* @i
  %9 = load i32, i32* @n
  %addtmp3 = add i32 %9, 1
  %cmptmp = icmp eq i32 %8, %addtmp3
  br i1 %cmptmp, label %repeat_cont, label %repeat_body

repeat_cont:                                      ; preds = %repeat_cond
  %10 = load i32, i32* @sum
  store i32 0, i32* @sum
  %11 = load i32, i32* @i
  store i32 1, i32* @i
  br label %repeat_body4

repeat_body4:                                     ; preds = %repeat_cond5, %repeat_cont
  %12 = load i32, i32* @sum
  %13 = load i32, i32* @sum
  %14 = load i32, i32* @i
  %15 = load [100 x i32], [100 x i32]* @r
  %subtmp7 = sub i32 %14, 1
  %ArrayCall8 = getelementptr [100 x i32], [100 x i32]* @r, i32 0, i32 %subtmp7
  %16 = load i32, i32* %ArrayCall8
  %addtmp9 = add i32 %13, %16
  store i32 %addtmp9, i32* @sum
  %17 = load i32, i32* @i
  %18 = load i32, i32* @i
  %addtmp10 = add i32 %18, 1
  store i32 %addtmp10, i32* @i
  br label %repeat_cond5

repeat_cond5:                                     ; preds = %repeat_body4
  %19 = load i32, i32* @i
  %20 = load i32, i32* @n
  %addtmp11 = add i32 %20, 1
  %cmptmp12 = icmp eq i32 %19, %addtmp11
  br i1 %cmptmp12, label %repeat_cont6, label %repeat_body4

repeat_cont6:                                     ; preds = %repeat_cond5
  %21 = load i32, i32* @sum
  %call_printf13 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format.2, i32 0, i32 0), i32 %21)
  ret i32 0
}

declare i32 @scanf(i8*, ...)

declare i32 @printf(i8*, ...)
