// RUN: llvm-mc -triple=aarch64 -show-encoding -mattr=+streaming-sve < %s \
// RUN:        | FileCheck %s --check-prefixes=CHECK-ENCODING,CHECK-INST
// RUN: not llvm-mc -triple=aarch64 -show-encoding -mattr=-neon < %s 2>&1 \
// RUN:        | FileCheck %s --check-prefix=CHECK-ERROR
// RUN: llvm-mc -triple=aarch64 -filetype=obj -mattr=+streaming-sve < %s \
// RUN:        | llvm-objdump -d - | FileCheck %s --check-prefix=CHECK-INST
// Disassemble encoding and check the re-encoding (-show-encoding) matches.
// RUN: llvm-mc -triple=aarch64 -show-encoding -mattr=+streaming-sve < %s \
// RUN:        | sed '/.text/d' | sed 's/.*encoding: //g' \
// RUN:        | llvm-mc -triple=aarch64 -mattr=+streaming-sve -disassemble -show-encoding \
// RUN:        | FileCheck %s --check-prefixes=CHECK-ENCODING,CHECK-INST

// Scalar FP instructions

fmulx s0, s1, s2
// CHECK-INST: fmulx s0, s1, s2
// CHECK-ENCODING: [0x20,0xdc,0x22,0x5e]
// CHECK-ERROR: instruction requires: streaming-sve or neon

fmulx d0, d1, d2
// CHECK-INST: fmulx d0, d1, d2
// CHECK-ENCODING: [0x20,0xdc,0x62,0x5e]
// CHECK-ERROR: instruction requires: streaming-sve or neon

frecps s0, s1, s2
// CHECK-INST: frecps s0, s1, s2
// CHECK-ENCODING: [0x20,0xfc,0x22,0x5e]
// CHECK-ERROR: instruction requires: streaming-sve or neon

frecps d0, d1, d2
// CHECK-INST: frecps d0, d1, d2
// CHECK-ENCODING: [0x20,0xfc,0x62,0x5e]
// CHECK-ERROR: instruction requires: streaming-sve or neon

frsqrts s0, s1, s2
// CHECK-INST: frsqrts s0, s1, s2
// CHECK-ENCODING: [0x20,0xfc,0xa2,0x5e]
// CHECK-ERROR: instruction requires: streaming-sve or neon

frsqrts d0, d1, d2
// CHECK-INST: frsqrts d0, d1, d2
// CHECK-ENCODING: [0x20,0xfc,0xe2,0x5e]
// CHECK-ERROR: instruction requires: streaming-sve or neon

frecpe s0, s1
// CHECK-INST: frecpe s0, s1
// CHECK-ENCODING: [0x20,0xd8,0xa1,0x5e]
// CHECK-ERROR: instruction requires: streaming-sve or neon

frecpe d0, d1
// CHECK-INST: frecpe d0, d1
// CHECK-ENCODING: [0x20,0xd8,0xe1,0x5e]
// CHECK-ERROR: instruction requires: streaming-sve or neon

frecpx s0, s1
// CHECK-INST: frecpx s0, s1
// CHECK-ENCODING: [0x20,0xf8,0xa1,0x5e]
// CHECK-ERROR: instruction requires: streaming-sve or neon

frecpx d0, d1
// CHECK-INST: frecpx d0, d1
// CHECK-ENCODING: [0x20,0xf8,0xe1,0x5e]
// CHECK-ERROR: instruction requires: streaming-sve or neon

frsqrte s0, s1
// CHECK-INST: frsqrte s0, s1
// CHECK-ENCODING: [0x20,0xd8,0xa1,0x7e]
// CHECK-ERROR: instruction requires: streaming-sve or neon

frsqrte d0, d1
// CHECK-INST: frsqrte d0, d1
// CHECK-ENCODING: [0x20,0xd8,0xe1,0x7e]
// CHECK-ERROR: instruction requires: streaming-sve or neon

// Vector to GPR integer move instructions

smov w0, v0.b[0]
// CHECK-INST: smov w0, v0.b[0]
// CHECK-ENCODING: [0x00,0x2c,0x01,0x0e]
// CHECK-ERROR: instruction requires: neon

smov x0, v0.b[0]
// CHECK-INST: smov x0, v0.b[0]
// CHECK-ENCODING: [0x00,0x2c,0x01,0x4e]
// CHECK-ERROR: instruction requires: neon

smov w0, v0.h[0]
// CHECK-INST: smov w0, v0.h[0]
// CHECK-ENCODING: [0x00,0x2c,0x02,0x0e]
// CHECK-ERROR: instruction requires: neon

smov x0, v0.h[0]
// CHECK-INST: smov x0, v0.h[0]
// CHECK-ENCODING: [0x00,0x2c,0x02,0x4e]
// CHECK-ERROR: instruction requires: neon

smov x0, v0.s[0]
// CHECK-INST: smov x0, v0.s[0]
// CHECK-ENCODING: [0x00,0x2c,0x04,0x4e]
// CHECK-ERROR: instruction requires: neon

umov w0, v0.b[0]
// CHECK-INST: umov w0, v0.b[0]
// CHECK-ENCODING: [0x00,0x3c,0x01,0x0e]
// CHECK-ERROR: instruction requires: neon

umov w0, v0.h[0]
// CHECK-INST: umov w0, v0.h[0]
// CHECK-ENCODING: [0x00,0x3c,0x02,0x0e]
// CHECK-ERROR: instruction requires: neon

umov w0, v0.s[0]
// CHECK-INST: mov w0, v0.s[0]
// CHECK-ENCODING: [0x00,0x3c,0x04,0x0e]
// CHECK-ERROR: instruction requires: neon

umov x0, v0.d[0]
// CHECK-INST: mov x0, v0.d[0]
// CHECK-ENCODING: [0x00,0x3c,0x08,0x4e]
// CHECK-ERROR: instruction requires: neon

// Aliases

mov w0, v0.s[0]
// CHECK-INST: mov w0, v0.s[0]
// CHECK-ENCODING: [0x00,0x3c,0x04,0x0e]
// CHECK-ERROR: instruction requires: neon

mov x0, v0.d[0]
// CHECK-INST: mov x0, v0.d[0]
// CHECK-ENCODING: [0x00,0x3c,0x08,0x4e]
// CHECK-ERROR: instruction requires: neon
