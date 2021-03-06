//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <forward_list>

// forward_list& operator=(const forward_list& x);

// Validate whether the container can be copy-assigned with an ADL-hijacking operator&

#include <forward_list>

#include "test_macros.h"
#include "operator_hijacker.h"

void test() {
  std::forward_list<operator_hijacker> lo;
  std::forward_list<operator_hijacker> l;
  l = lo;
}
