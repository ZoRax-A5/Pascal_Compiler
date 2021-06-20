; ModuleID = 'pascal_module'
source_filename = "pascal_module"

@r = common global [100 x i32] zeroinitializer
@i = common global i32 0
@j = common global i32 0
@n = common global i32 0
@temp = common global i32 0
@flag = common global i1 false
@scanf_format = private unnamed_addr constant [9 x i8] c"%d%*[^\0A]\00", align 1
@scanf_newline = private unnamed_addr constant [4 x i8] c"%*c\00", align 1
@scanf_format.1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@printf_format = private unnamed_addr constant [6 x i8] c"%d%d\0A\00", align 1
@printf_format.2 = private unnamed_addr constant [5 x i8] c"%d%c\00", align 1
@printf_format.3 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

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
  %9 = load i32, i32* @i
  store i32 1, i32* @i
  br label %repeat_body4

repeat_body4:                                     ; preds = %repeat_cond5, %repeat_cont
  %10 = load i1, i1* @flag
  store i1 true, i1* @flag
  %11 = load i32, i32* @j
  %12 = load i32, i32* @n
  %subtmp7 = sub i32 %12, 1
  store i32 %subtmp7, i32* @j
  br label %repeat_body8

repeat_cond5:                                     ; preds = %if_cont32
  %13 = load i32, i32* @i
  %14 = load i32, i32* @n
  %cmptmp34 = icmp eq i32 %13, %14
  br i1 %cmptmp34, label %repeat_cont6, label %repeat_body4

repeat_cont6:                                     ; preds = %repeat_cond5, %if_then30
  %15 = load i32, i32* @i
  store i32 1, i32* @i
  br label %repeat_body35

repeat_body8:                                     ; preds = %repeat_cond9, %repeat_body4
  %16 = load i32, i32* @j
  %addtmp11 = add i32 %16, 1
  %17 = load [100 x i32], [100 x i32]* @r
  %subtmp12 = sub i32 %addtmp11, 1
  %ArrayCall13 = getelementptr [100 x i32], [100 x i32]* @r, i32 0, i32 %subtmp12
  %18 = load i32, i32* %ArrayCall13
  %19 = load i32, i32* @j
  %20 = load [100 x i32], [100 x i32]* @r
  %subtmp14 = sub i32 %19, 1
  %ArrayCall15 = getelementptr [100 x i32], [100 x i32]* @r, i32 0, i32 %subtmp14
  %21 = load i32, i32* %ArrayCall15
  %cmptmp16 = icmp slt i32 %18, %21
  br i1 %cmptmp16, label %if_then, label %if_else

repeat_cond9:                                     ; preds = %if_cont
  %22 = load i32, i32* @j
  %23 = load i32, i32* @i
  %subtmp28 = sub i32 %23, 1
  %cmptmp29 = icmp eq i32 %22, %subtmp28
  br i1 %cmptmp29, label %repeat_cont10, label %repeat_body8

repeat_cont10:                                    ; preds = %repeat_cond9
  %24 = load i1, i1* @flag
  br i1 %24, label %if_then30, label %if_else31

if_then:                                          ; preds = %repeat_body8
  %25 = load i32, i32* @i
  %26 = load i32, i32* @j
  %call_printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @printf_format, i32 0, i32 0), i32 %25, i32 %26)
  %27 = load i32, i32* @temp
  %28 = load i32, i32* @j
  %addtmp17 = add i32 %28, 1
  %29 = load [100 x i32], [100 x i32]* @r
  %subtmp18 = sub i32 %addtmp17, 1
  %ArrayCall19 = getelementptr [100 x i32], [100 x i32]* @r, i32 0, i32 %subtmp18
  %30 = load i32, i32* %ArrayCall19
  store i32 %30, i32* @temp
  %31 = load i32, i32* @j
  %addtmp20 = add i32 %31, 1
  %32 = load [100 x i32], [100 x i32]* @r
  %subtmp21 = sub i32 %addtmp20, 1
  %ArrayCall22 = getelementptr [100 x i32], [100 x i32]* @r, i32 0, i32 %subtmp21
  %33 = load i32, i32* %ArrayCall22
  %34 = load i32, i32* @j
  %35 = load [100 x i32], [100 x i32]* @r
  %subtmp23 = sub i32 %34, 1
  %ArrayCall24 = getelementptr [100 x i32], [100 x i32]* @r, i32 0, i32 %subtmp23
  %36 = load i32, i32* %ArrayCall24
  store i32 %36, i32* %ArrayCall22
  %37 = load i32, i32* @j
  %38 = load [100 x i32], [100 x i32]* @r
  %subtmp25 = sub i32 %37, 1
  %ArrayCall26 = getelementptr [100 x i32], [100 x i32]* @r, i32 0, i32 %subtmp25
  %39 = load i32, i32* %ArrayCall26
  %40 = load i32, i32* @temp
  store i32 %40, i32* %ArrayCall26
  %41 = load i1, i1* @flag
  store i1 false, i1* @flag
  br label %if_cont

if_else:                                          ; preds = %repeat_body8
  br label %if_cont

if_cont:                                          ; preds = %if_else, %if_then
  %42 = load i32, i32* @j
  %43 = load i32, i32* @j
  %subtmp27 = sub i32 %43, 1
  store i32 %subtmp27, i32* @j
  br label %repeat_cond9

if_then30:                                        ; preds = %repeat_cont10
  br label %repeat_cont6

if_else31:                                        ; preds = %repeat_cont10
  br label %if_cont32

if_cont32:                                        ; preds = %if_else31, %break_cont
  %44 = load i32, i32* @i
  %45 = load i32, i32* @i
  %addtmp33 = add i32 %45, 1
  store i32 %addtmp33, i32* @i
  br label %repeat_cond5

break_cont:                                       ; No predecessors!
  br label %if_cont32

repeat_body35:                                    ; preds = %repeat_cond36, %repeat_cont6
  %46 = load i32, i32* @i
  %47 = load i32, i32* @n
  %cmptmp41 = icmp slt i32 %46, %47
  br i1 %cmptmp41, label %if_then38, label %if_else39

repeat_cond36:                                    ; preds = %if_cont40
  %48 = load i32, i32* @i
  %49 = load i32, i32* @n
  %addtmp49 = add i32 %49, 1
  %cmptmp50 = icmp eq i32 %48, %addtmp49
  br i1 %cmptmp50, label %repeat_cont37, label %repeat_body35

repeat_cont37:                                    ; preds = %repeat_cond36
  ret i32 0

if_then38:                                        ; preds = %repeat_body35
  %50 = load i32, i32* @i
  %51 = load [100 x i32], [100 x i32]* @r
  %subtmp42 = sub i32 %50, 1
  %ArrayCall43 = getelementptr [100 x i32], [100 x i32]* @r, i32 0, i32 %subtmp42
  %52 = load i32, i32* %ArrayCall43
  %call_printf44 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @printf_format.2, i32 0, i32 0), i32 %52, i8 32)
  br label %if_cont40

if_else39:                                        ; preds = %repeat_body35
  %53 = load i32, i32* @i
  %54 = load [100 x i32], [100 x i32]* @r
  %subtmp45 = sub i32 %53, 1
  %ArrayCall46 = getelementptr [100 x i32], [100 x i32]* @r, i32 0, i32 %subtmp45
  %55 = load i32, i32* %ArrayCall46
  %call_printf47 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format.3, i32 0, i32 0), i32 %55)
  br label %if_cont40

if_cont40:                                        ; preds = %if_else39, %if_then38
  %56 = load i32, i32* @i
  %57 = load i32, i32* @i
  %addtmp48 = add i32 %57, 1
  store i32 %addtmp48, i32* @i
  br label %repeat_cond36
}

declare i32 @scanf(i8*, ...)

declare i32 @printf(i8*, ...)
