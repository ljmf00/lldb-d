//===-- DLanguage.cpp -----------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "DLanguage.h"
#include "DTypeUtils.h"
#include "DFormatterFunctions.h"

#include "lldb/Core/PluginManager.h"
#include "lldb/Core/Mangled.h"
#include "lldb/DataFormatters/DataVisualization.h"
#include "lldb/DataFormatters/FormattersHelpers.h"
#include "lldb/lldb-enumerations.h"

using namespace lldb;
using namespace lldb_private;

LLDB_PLUGIN_DEFINE(DLanguage)

void DLanguage::Initialize() {
  PluginManager::RegisterPlugin(GetPluginNameStatic(), "D Language",
                                CreateInstance);
}

void DLanguage::Terminate() {
  PluginManager::UnregisterPlugin(CreateInstance);
}

bool DLanguage::IsNilReference(ValueObject &valobj) {
  // not an object from D
  if (valobj.GetObjectRuntimeLanguage() != eLanguageTypeD)
    return false;

  // a normal pointer
  if (valobj.IsPointerType())
  {
    bool canReadValue;
    bool isZero = valobj.GetValueAsUnsigned(0, &canReadValue) == 0;
    return canReadValue && isZero;
  }

  lldb::addr_t valobj_addr;
  uint64_t length;

  // not a slice
  if (!IsDSlice(valobj, nullptr, &valobj_addr, &length))
    return false;

  // in D an empty array == null
  if (valobj_addr == 0 || length == 0)
    return true;

  // non-empty array with a non-null pointer
  return false;
}

HardcodedFormatters::HardcodedSyntheticFinder
DLanguage::GetHardcodedSynthetics() {
  static llvm::once_flag g_initialize;
  static HardcodedFormatters::HardcodedSyntheticFinder g_formatters;

  llvm::call_once(g_initialize, []() -> void {
    g_formatters.push_back([](lldb_private::ValueObject &valobj,
                              lldb::DynamicValueType,
                              FormatManager &
                                  fmt_mgr) -> SyntheticChildren::SharedPointer {
      static CXXSyntheticChildren::SharedPointer formatter_sp(
          new CXXSyntheticChildren(
              SyntheticChildren::Flags()
                  .SetCascades(true)
                  .SetSkipPointers(true)
                  .SetSkipReferences(true)
                  .SetNonCacheable(true),
              "D array slice synthetic children",
              lldb_private::formatters::DSliceSyntheticFrontEndCreator));

      if (IsDSlice(valobj, nullptr, nullptr, nullptr) && !IsDStringSlice(valobj, nullptr, nullptr, nullptr))
        return formatter_sp;

      return nullptr;
    });
  });

  return g_formatters;
}

HardcodedFormatters::HardcodedSummaryFinder
DLanguage::GetHardcodedSummaries() {
  static llvm::once_flag g_initialize;
  static HardcodedFormatters::HardcodedSummaryFinder g_formatters;

  llvm::call_once(g_initialize, []() -> void {
    g_formatters.push_back(
        [](lldb_private::ValueObject &valobj, lldb::DynamicValueType,
           FormatManager &fmt_mgr) -> TypeSummaryImpl::SharedPointer {
          static CXXFunctionSummaryFormat::SharedPointer formatter_sp(
              new CXXFunctionSummaryFormat(
                  TypeSummaryImpl::Flags()
                      .SetCascades(true)
                      .SetSkipPointers(true)
                      .SetSkipReferences(true)
                      .SetNonCacheable(true)
                      .SetDontShowChildren(true)
                      .SetDontShowValue(true)
                      .SetShowMembersOneLiner(false)
                      .SetHideItemNames(false),
                  lldb_private::formatters::DStringSliceSummaryProvider,
                  "D string slice summary provider"));

          if (IsDStringSlice(valobj, nullptr, nullptr, nullptr))
            return formatter_sp;

          return nullptr;
        });
  });

  return g_formatters;
}

bool DLanguage::IsSourceFile(llvm::StringRef file_path) const {
  const auto suffixes = {".d", ".dd", ".di"};
  for (const auto *const suffix : suffixes)
    if (file_path.endswith_insensitive(suffix))
      return true;

  // not a D source file
  return false;
}

Language *DLanguage::CreateInstance(lldb::LanguageType language) {
  if (language == eLanguageTypeD)
    return new DLanguage();

  // not D
  return nullptr;
}

bool DLanguage::SymbolNameFitsToLanguage(Mangled mangled) const {
  const char *mangled_name = mangled.GetMangledName().GetCString();
  return mangled_name && Mangled::GetManglingScheme(mangled_name) == Mangled::eManglingSchemeD;
}
