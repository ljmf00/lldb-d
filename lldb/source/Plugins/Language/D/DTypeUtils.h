//===-- DTypeUtils.h --------------------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLDB_SOURCE_PLUGINS_LANGUAGE_D_DTYPEUTILS_H
#define LLDB_SOURCE_PLUGINS_LANGUAGE_D_DTYPEUTILS_H

#include "lldb/lldb-forward.h"
#include "lldb/Core/ValueObject.h"

using namespace lldb;

namespace lldb_private {

bool IsDSlice(ValueObject &Valobj, CompilerType* Type, addr_t* AddrData,
              uint64_t* Len);

bool IsDStringSlice(ValueObject &Valobj, CompilerType* Type, addr_t* AddrData,
                    uint64_t* Len);

bool IsCharType(CompilerType Type);

} // namespace lldb_private

#endif // LLDB_SOURCE_PLUGINS_LANGUAGE_D_DTYPEUTILS_H
