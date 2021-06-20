; ModuleID = 'pascal_module'
source_filename = "pascal_module"

@r = common global i32 0
@i = common global i32 0
@j = common global i32 0
@n = common global i32 0
@temp = common global i32 0
@flag = common global i1 false
@scanf_format = private unnamed_addr constant [9 x i8] c"%d%*[^\0A]\00"
@scanf_newline = private unnamed_addr constant [4 x i8] c"%*c\00"
@scanf_format.1 = private unnamed_addr constant [3 x i8] c"%d\00"
@printf_format = private unnamed_addr constant [6 x i8] c"%d%d\0A\00"
@printf_format.2 = private unnamed_addr constant [5 x i8] c"%d%c\00"
@printf_format.3 = private unnamed_addr constant [4 x i8] c"%d\0A\00"

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
  %5 = load i32, i32* @i
  %addtmp = add i32 %5, 1
  store i32 %addtmp, i32* @i
  br label %repeat_cond

repeat_cond:                                      ; preds = %repeat_body
  %6 = load i32, i32* @i
  %7 = load i32, i32* @n
  %addtmp3 = add i32 %7, 1
  %cmptmp = icmp eq i32 %6, %addtmp3
  br i1 %cmptmp, label %repeat_cont, label %repeat_body

repeat_cont:                                      ; preds = %repeat_cond
  %8 = load i32, i32* @i
  store i32 1, i32* @i
  br label %repeat_body4

repeat_body4:                                     ; preds = %repeat_cond5, %repeat_cont
  %9 = load i1, i1* @flag
  store i1 true, i1* @flag
  %10 = load i32, i32* @j
  %11 = load i32, i32* @n
  %subtmp = sub i32 %11, 1
  store i32 %subtmp, i32* @j
  br label %repeat_body7

repeat_cond5:                                     ; preds = %if_cont19
  %12 = load i32, i32* @i
  %13 = load i32, i32* @n
  %cmptmp21 = icmp eq i32 %12, %13
  br i1 %cmptmp21, label %repeat_cont6, label %repeat_body4

repeat_cont6:                                     ; preds = %repeat_cond5, %if_then17
  %14 = load i32, i32* @i
  store i32 1, i32* @i
  br label %repeat_body22

repeat_body7:                                     ; preds = %repeat_cond8, %repeat_body4
  %15 = load i32, i32* @j
  %addtmp10 = add i32 %15, 1
  %16 = load i32, i32* @r
  %17 = load i32, i32* @j
  %18 = load i32, i32* @r
  %cmptmp11 = icmp slt i32 %16, %18
  br i1 %cmptmp11, label %if_then, label %if_else

repeat_cond8:                                     ; preds = %if_cont
  %19 = load i32, i32* @j
  %20 = load i32, i32* @i
  %subtmp15 = sub i32 %20, 1
  %cmptmp16 = icmp eq i32 %19, %subtmp15
  br i1 %cmptmp16, label %repeat_cont9, label %repeat_body7

repeat_cont9:                                     ; preds = %repeat_cond8
  %21 = load i1, i1* @flag
  br i1 %21, label %if_then17, label %if_else18

if_then:                                          ; preds = %repeat_body7
  %22 = load i32, i32* @i
  %23 = load i32, i32* @j
  %call_printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @printf_format, i32 0, i32 0), i32 %22, i32 %23)
  %24 = load i32, i32* @temp
  %25 = load i32, i32* @j
  %addtmp12 = add i32 %25, 1
  %26 = load i32, i32* @r
  store i32 %26, i32* @temp
  %27 = load i32, i32* @j
  %addtmp13 = add i32 %27, 1
  %28 = load i32, i32* @r
  %29 = load i32, i32* @j
  %30 = load i32, i32* @r
  store i32 %30, i32* @r
  %31 = load i32, i32* @j
  %32 = load i32, i32* @r
  %33 = load i32, i32* @temp
  store i32 %33, i32* @r
  %34 = load i1, i1* @flag
  store i1 false, i1* @flag
  br label %if_cont

if_else:                                          ; preds = %repeat_body7
  br label %if_cont

if_cont:                                          ; preds = %if_else, %if_then
  %35 = load i32, i32* @j
  %36 = load i32, i32* @j
  %subtmp14 = sub i32 %36, 1
  store i32 %subtmp14, i32* @j
  br label %repeat_cond8

if_then17:                                        ; preds = %repeat_cont9
  br label %repeat_cont6

if_else18:                                        ; preds = %repeat_cont9
  br label %if_cont19

if_cont19:                                        ; preds = %if_else18, %break_cont
  %37 = load i32, i32* @i
  %38 = load i32, i32* @i
  %addtmp20 = add i32 %38, 1
  store i32 %addtmp20, i32* @i
  br label %repeat_cond5

break_cont:                                       ; No predecessors!
  br label %if_cont19

repeat_body22:                                    ; preds = %repeat_cond23, %repeat_cont6
  %39 = load i32, i32* @i
  %40 = load i32, i32* @n
  %cmptmp28 = icmp slt i32 %39, %40
  br i1 %cmptmp28, label %if_then25, label %if_else26

repeat_cond23:                                    ; preds = %if_cont27
  %41 = load i32, i32* @i
  %42 = load i32, i32* @n
  %addtmp32 = add i32 %42, 1
  %cmptmp33 = icmp eq i32 %41, %addtmp32
  br i1 %cmptmp33, label %repeat_cont24, label %repeat_body22

repeat_cont24:                                    ; preds = %repeat_cond23
  ret i32 0

if_then25:                                        ; preds = %repeat_body22
  %43 = load i32, i32* @i
  %44 = load i32, i32* @r
  %call_printf29 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @printf_format.2, i32 0, i32 0), i32 %44, i8 32)
  br label %if_cont27

if_else26:                                        ; preds = %repeat_body22
  %45 = load i32, i32* @i
  %46 = load i32, i32* @r
  %call_printf30 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format.3, i32 0, i32 0), i32 %46)
  br label %if_cont27

if_cont27:                                        ; preds = %if_else26, %if_then25
  %47 = load i32, i32* @i
  %48 = load i32, i32* @i
  %addtmp31 = add i32 %48, 1
  store i32 %addtmp31, i32* @i
  br label %repeat_cond23
}

declare i32 @scanf(i8*, ...)

declare i32 @printf(i8*, ...)
