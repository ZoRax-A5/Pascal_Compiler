; ModuleID = 'pascal_module'
source_filename = "pascal_module"

@a = common constant i32 3
@printf_format = private unnamed_addr constant [4 x i8] c"%d\0A\00"

define i32 @main() {
entry:
  %0 = load i32, i32* @a
  %call_printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format, i32 0, i32 0), i32 %0)
  ret i32 0
}

declare i32 @printf(i8*, ...)
