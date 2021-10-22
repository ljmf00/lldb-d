//===-- DFormatterFunctions.h ---------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLDB_SOURCE_PLUGINS_LANGUAGE_D_DFORMATTERFUNCTIONS_H
#define LLDB_SOURCE_PLUGINS_LANGUAGE_D_DFORMATTERFUNCTIONS_H

#include "lldb/lldb-forward.h"
#include "lldb/DataFormatters/TypeSynthetic.h"

namespace lldb_private {
namespace formatters {

SyntheticChildrenFrontEnd *
DSliceSyntheticFrontEndCreator(CXXSyntheticChildren *,
                               lldb::ValueObjectSP valobj_sp);

bool DStringSliceSummaryProvider(
    ValueObject &valobj, Stream &stream, const TypeSummaryOptions &);

} // namespace formatters
} // namespace lldb_private

#endif // LLDB_SOURCE_PLUGINS_LANGUAGE_D_DFORMATTERFUNCTIONS_H
