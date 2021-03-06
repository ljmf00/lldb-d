; NOTE: Assertions have been autogenerated by utils/update_test_checks.py
; RUN: opt < %s -instcombine -S | FileCheck %s

define float @select_fadd(i1 %cond, float %A, float %B) {
; CHECK-LABEL: @select_fadd(
; CHECK-NEXT:    [[C:%.*]] = fadd float [[A:%.*]], [[B:%.*]]
; CHECK-NEXT:    [[D:%.*]] = select i1 [[COND:%.*]], float [[C]], float [[A]]
; CHECK-NEXT:    ret float [[D]]
;
  %C = fadd float %A, %B
  %D = select i1 %cond, float %C, float %A
  ret float %D
}

define float @select_fadd_swapped(i1 %cond, float %A, float %B) {
; CHECK-LABEL: @select_fadd_swapped(
; CHECK-NEXT:    [[C:%.*]] = fadd float [[A:%.*]], [[B:%.*]]
; CHECK-NEXT:    [[D:%.*]] = select i1 [[COND:%.*]], float [[A]], float [[C]]
; CHECK-NEXT:    ret float [[D]]
;
  %C = fadd float %A, %B
  %D = select i1 %cond, float %A, float %C
  ret float %D
}

define float @select_fadd_fast_math(i1 %cond, float %A, float %B) {
; CHECK-LABEL: @select_fadd_fast_math(
; CHECK-NEXT:    [[C:%.*]] = fadd fast float [[A:%.*]], [[B:%.*]]
; CHECK-NEXT:    [[D:%.*]] = select i1 [[COND:%.*]], float [[C]], float [[A]]
; CHECK-NEXT:    ret float [[D]]
;
  %C = fadd fast float %A, %B
  %D = select i1 %cond, float %C, float %A
  ret float %D
}

define float @select_fadd_swapped_fast_math(i1 %cond, float %A, float %B) {
; CHECK-LABEL: @select_fadd_swapped_fast_math(
; CHECK-NEXT:    [[C:%.*]] = fadd fast float [[A:%.*]], [[B:%.*]]
; CHECK-NEXT:    [[D:%.*]] = select i1 [[COND:%.*]], float [[A]], float [[C]]
; CHECK-NEXT:    ret float [[D]]
;
  %C = fadd fast float %A, %B
  %D = select i1 %cond, float %A, float %C
  ret float %D
}

define float @select_fmul(i1 %cond, float %A, float %B) {
; CHECK-LABEL: @select_fmul(
; CHECK-NEXT:    [[C:%.*]] = fmul float [[A:%.*]], [[B:%.*]]
; CHECK-NEXT:    [[D:%.*]] = select i1 [[COND:%.*]], float [[C]], float [[A]]
; CHECK-NEXT:    ret float [[D]]
;
  %C = fmul float %A, %B
  %D = select i1 %cond, float %C, float %A
  ret float %D
}

define float @select_fmul_swapped(i1 %cond, float %A, float %B) {
; CHECK-LABEL: @select_fmul_swapped(
; CHECK-NEXT:    [[C:%.*]] = fmul float [[A:%.*]], [[B:%.*]]
; CHECK-NEXT:    [[D:%.*]] = select i1 [[COND:%.*]], float [[A]], float [[C]]
; CHECK-NEXT:    ret float [[D]]
;
  %C = fmul float %A, %B
  %D = select i1 %cond, float %A, float %C
  ret float %D
}

define float @select_fmul_fast_math(i1 %cond, float %A, float %B) {
; CHECK-LABEL: @select_fmul_fast_math(
; CHECK-NEXT:    [[C:%.*]] = fmul fast float [[A:%.*]], [[B:%.*]]
; CHECK-NEXT:    [[D:%.*]] = select i1 [[COND:%.*]], float [[C]], float [[A]]
; CHECK-NEXT:    ret float [[D]]
;
  %C = fmul fast float %A, %B
  %D = select i1 %cond, float %C, float %A
  ret float %D
}

define float @select_fmul_swapped_fast_math(i1 %cond, float %A, float %B) {
; CHECK-LABEL: @select_fmul_swapped_fast_math(
; CHECK-NEXT:    [[C:%.*]] = fmul fast float [[A:%.*]], [[B:%.*]]
; CHECK-NEXT:    [[D:%.*]] = select i1 [[COND:%.*]], float [[A]], float [[C]]
; CHECK-NEXT:    ret float [[D]]
;
  %C = fmul fast float %A, %B
  %D = select i1 %cond, float %A, float %C
  ret float %D
}

define float @select_fsub(i1 %cond, float %A, float %B) {
; CHECK-LABEL: @select_fsub(
; CHECK-NEXT:    [[C:%.*]] = fsub float [[A:%.*]], [[B:%.*]]
; CHECK-NEXT:    [[D:%.*]] = select i1 [[COND:%.*]], float [[C]], float [[A]]
; CHECK-NEXT:    ret float [[D]]
;
  %C = fsub float %A, %B
  %D = select i1 %cond, float %C, float %A
  ret float %D
}

define float @select_fsub_swapped(i1 %cond, float %A, float %B) {
; CHECK-LABEL: @select_fsub_swapped(
; CHECK-NEXT:    [[C:%.*]] = fsub float [[A:%.*]], [[B:%.*]]
; CHECK-NEXT:    [[D:%.*]] = select i1 [[COND:%.*]], float [[A]], float [[C]]
; CHECK-NEXT:    ret float [[D]]
;
  %C = fsub float %A, %B
  %D = select i1 %cond, float %A, float %C
  ret float %D
}

define float @select_fsub_fast_math(i1 %cond, float %A, float %B) {
; CHECK-LABEL: @select_fsub_fast_math(
; CHECK-NEXT:    [[C:%.*]] = fsub fast float [[A:%.*]], [[B:%.*]]
; CHECK-NEXT:    [[D:%.*]] = select i1 [[COND:%.*]], float [[C]], float [[A]]
; CHECK-NEXT:    ret float [[D]]
;
  %C = fsub fast float %A, %B
  %D = select i1 %cond, float %C, float %A
  ret float %D
}

define float @select_fsub_swapped_fast_math(i1 %cond, float %A, float %B) {
; CHECK-LABEL: @select_fsub_swapped_fast_math(
; CHECK-NEXT:    [[C:%.*]] = fsub fast float [[A:%.*]], [[B:%.*]]
; CHECK-NEXT:    [[D:%.*]] = select i1 [[COND:%.*]], float [[A]], float [[C]]
; CHECK-NEXT:    ret float [[D]]
;
  %C = fsub fast float %A, %B
  %D = select i1 %cond, float %A, float %C
  ret float %D
}

; 'fsub' can only fold on the amount subtracted.
define float @select_fsub_invalid(i1 %cond, float %A, float %B) {
; CHECK-LABEL: @select_fsub_invalid(
; CHECK-NEXT:    [[C:%.*]] = fsub float [[B:%.*]], [[A:%.*]]
; CHECK-NEXT:    [[D:%.*]] = select i1 [[COND:%.*]], float [[C]], float [[A]]
; CHECK-NEXT:    ret float [[D]]
;
  %C = fsub float %B, %A
  %D = select i1 %cond, float %C, float %A
  ret float %D
}

define float @select_fdiv(i1 %cond, float %A, float %B) {
; CHECK-LABEL: @select_fdiv(
; CHECK-NEXT:    [[C:%.*]] = fdiv float [[A:%.*]], [[B:%.*]]
; CHECK-NEXT:    [[D:%.*]] = select i1 [[COND:%.*]], float [[C]], float [[A]]
; CHECK-NEXT:    ret float [[D]]
;
  %C = fdiv float %A, %B
  %D = select i1 %cond, float %C, float %A
  ret float %D
}

define float @select_fdiv_swapped(i1 %cond, float %A, float %B) {
; CHECK-LABEL: @select_fdiv_swapped(
; CHECK-NEXT:    [[C:%.*]] = fdiv float [[A:%.*]], [[B:%.*]]
; CHECK-NEXT:    [[D:%.*]] = select i1 [[COND:%.*]], float [[A]], float [[C]]
; CHECK-NEXT:    ret float [[D]]
;
  %C = fdiv float %A, %B
  %D = select i1 %cond, float %A, float %C
  ret float %D
}

define float @select_fdiv_fast_math(i1 %cond, float %A, float %B) {
; CHECK-LABEL: @select_fdiv_fast_math(
; CHECK-NEXT:    [[C:%.*]] = fdiv fast float [[A:%.*]], [[B:%.*]]
; CHECK-NEXT:    [[D:%.*]] = select i1 [[COND:%.*]], float [[C]], float [[A]]
; CHECK-NEXT:    ret float [[D]]
;
  %C = fdiv fast float %A, %B
  %D = select i1 %cond, float %C, float %A
  ret float %D
}

define float @select_fdiv_swapped_fast_math(i1 %cond, float %A, float %B) {
; CHECK-LABEL: @select_fdiv_swapped_fast_math(
; CHECK-NEXT:    [[C:%.*]] = fdiv fast float [[A:%.*]], [[B:%.*]]
; CHECK-NEXT:    [[D:%.*]] = select i1 [[COND:%.*]], float [[A]], float [[C]]
; CHECK-NEXT:    ret float [[D]]
;
  %C = fdiv fast float %A, %B
  %D = select i1 %cond, float %A, float %C
  ret float %D
}

; 'fdiv' can only fold on the divisor amount.
define float @select_fdiv_invalid(i1 %cond, float %A, float %B) {
; CHECK-LABEL: @select_fdiv_invalid(
; CHECK-NEXT:    [[C:%.*]] = fdiv float [[B:%.*]], [[A:%.*]]
; CHECK-NEXT:    [[D:%.*]] = select i1 [[COND:%.*]], float [[C]], float [[A]]
; CHECK-NEXT:    ret float [[D]]
;
  %C = fdiv float %B, %A
  %D = select i1 %cond, float %C, float %A
  ret float %D
}
