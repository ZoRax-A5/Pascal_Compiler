; ModuleID = 'pascal_module'
source_filename = "pascal_module"

@a = common global i32 0
@b = common global double 0.000000e+00
@c = common global i8 0
@d = common global i1 false
@e = common global double 0.000000e+00
@f = common global i32 0
@n = common global i32 0

define i32 @main() {
entry:
  %0 = load i32, i32* @f
  store i32 3, i32* @f
  %1 = load i32, i32* @a
  store i32 -3, i32* @a
  %2 = load double, double* @b
  store double 3.200000e+00, double* @b
  %3 = load i32, i32* @a
  %4 = load double, double* @b
  %5 = load i8, i8* @c
  store i8 99, i8* @c
  %6 = load i1, i1* @d
  store i1 true, i1* @d
  %7 = load double, double* @e
  %8 = load i32, i32* @a
  %9 = load double, double* @b
  %10 = uitofp i32 %8 to double
  %addftmp = fadd double %10, %9
  store double %addftmp, double* @e
  %11 = load double, double* @e
  %12 = load double, double* @b
  %addftmp1 = fadd double 3.000000e+00, %12
  store double %addftmp1, double* @e
  %13 = load double, double* @e
  store double 6.200000e+00, double* @e
  %14 = load double, double* @e
  %15 = load i32, i32* @a
  %16 = load double, double* @b
  %17 = uitofp i32 %15 to double
  %addftmp2 = fadd double %17, %16
  %addftmp3 = fadd double %addftmp2, 3.000000e+00
  store double %addftmp3, double* @e
  %18 = load double, double* @e
  %19 = load i32, i32* @a
  %20 = load double, double* @b
  %21 = uitofp i32 %19 to double
  %mulftmp = fmul double %21, %20
  store double %mulftmp, double* @e
  %22 = load i32, i32* @a
  %23 = load double, double* @b
  %24 = uitofp i32 %22 to double
  %cmpftmp = fcmp olt double %24, %23
  br i1 %cmpftmp, label %if_then, label %if_else

if_then:                                          ; preds = %entry
  %25 = load i32, i32* @a
  store i32 1, i32* @a
  br label %if_cont

if_else:                                          ; preds = %entry
  %26 = load double, double* @b
  store double 2.300000e+00, double* @b
  br label %if_cont

if_cont:                                          ; preds = %if_else, %if_then
  br label %repeat_body

repeat_body:                                      ; preds = %repeat_cond, %if_cont
  %27 = load i32, i32* @a
  %28 = load i32, i32* @a
  %addtmp = add i32 %28, 1
  store i32 %addtmp, i32* @a
  %29 = load double, double* @b
  %30 = load i32, i32* @a
  %31 = load double, double* @b
  %32 = uitofp i32 %30 to double
  %mulftmp4 = fmul double %32, %31
  store double %mulftmp4, double* @b
  br label %repeat_cond

repeat_cond:                                      ; preds = %repeat_body
  %33 = load i32, i32* @a
  %cmptmp = icmp eq i32 %33, 19
  br i1 %cmptmp, label %repeat_cont, label %repeat_body

repeat_cont:                                      ; preds = %repeat_cond
  br label %while_cond

while_cond:                                       ; preds = %while_body, %repeat_cont
  %34 = load i32, i32* @a
  %cmptmp5 = icmp slt i32 %34, 30
  br i1 %cmptmp5, label %while_body, label %while_end

while_body:                                       ; preds = %while_cond
  %35 = load i32, i32* @a
  %36 = load i32, i32* @a
  %addtmp6 = add i32 %36, 1
  store i32 %addtmp6, i32* @a
  br label %while_cond

while_end:                                        ; preds = %while_cond
  ret i32 0
}

define void @mine(i32* %0, i32* %1, double* %2) {
entry:
  %3 = load i32, i32* %0
  %x = alloca i32
  store i32 %3, i32* %x
  %4 = load i32, i32* %1
  %y = alloca i32
  store i32 %4, i32* %y
  %5 = load double, double* %2
  %c = alloca double
  store double %5, double* %c
  %6 = load double, double* %c
  store double 3.000000e+00, double* %c
  ret void
}
