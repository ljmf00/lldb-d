; NOTE: Assertions have been autogenerated by utils/update_test_checks.py
; RUN: opt < %s -instcombine -S | FileCheck %s

define i32 @foo(i32 %a) {
; CHECK-LABEL: @foo(
; CHECK-NEXT:    [[TMP1:%.*]] = add i32 [[A:%.*]], -100
; CHECK-NEXT:    [[TMP2:%.*]] = icmp slt i32 [[TMP1]], -1
; CHECK-NEXT:    [[A_OP:%.*]] = add i32 [[A]], 1
; CHECK-NEXT:    [[T13:%.*]] = select i1 [[TMP2]], i32 100, i32 [[A_OP]]
; CHECK-NEXT:    ret i32 [[T13]]
;
  %t15 = sub i32 99, %a
  %t16 = icmp slt i32 %t15, 0
  %smax = select i1 %t16, i32 0, i32 %t15
  %t12 = add i32 %smax, %a
  %t13 = add i32 %t12, 1
  ret i32 %t13
}

define i32 @bar(i32 %a) {
; CHECK-LABEL: @bar(
; CHECK-NEXT:    [[TMP1:%.*]] = add i32 [[A:%.*]], -100
; CHECK-NEXT:    [[TMP2:%.*]] = icmp slt i32 [[TMP1]], -1
; CHECK-NEXT:    [[T12:%.*]] = select i1 [[TMP2]], i32 99, i32 [[A]]
; CHECK-NEXT:    ret i32 [[T12]]
;
  %t15 = sub i32 99, %a
  %t16 = icmp slt i32 %t15, 0
  %smax = select i1 %t16, i32 0, i32 %t15
  %t12 = add i32 %smax, %a
  ret i32 %t12
}

define i32 @fun(i32 %a) {
; CHECK-LABEL: @fun(
; CHECK-NEXT:    [[T16:%.*]] = icmp slt i32 [[A:%.*]], 0
; CHECK-NEXT:    [[T12:%.*]] = select i1 [[T16]], i32 [[A]], i32 99
; CHECK-NEXT:    ret i32 [[T12]]
;
  %t15 = sub i32 99, %a
  %t16 = icmp slt i32 %a, 0
  %smax = select i1 %t16, i32 0, i32 %t15
  %t12 = add i32 %smax, %a
  ret i32 %t12
}
