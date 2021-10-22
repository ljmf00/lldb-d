//===-- DLanguage.h ---------------------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLDB_SOURCE_PLUGINS_LANGUAGE_D_DLANGUAGE_H
#define LLDB_SOURCE_PLUGINS_LANGUAGE_D_DLANGUAGE_H

#include "lldb/Target/Language.h"
#include "llvm/ADT/StringRef.h"

namespace lldb_private {

class DLanguage : public Language {
	public:
  DLanguage() = default;

  ~DLanguage() override = default;

  // Static Functions
  static void Initialize();

  static void Terminate();

  static lldb_private::Language *CreateInstance(lldb::LanguageType language);

  lldb::LanguageType GetLanguageType() const override {
    return lldb::eLanguageTypeD;
  }

  bool IsNilReference(ValueObject &valobj) override;

  llvm::StringRef GetNilReferenceSummaryString() override { return "null"; }

  static llvm::StringRef GetPluginNameStatic() { return "dlang"; }

  llvm::StringRef GetPluginName() override { return GetPluginNameStatic(); }

  bool IsSourceFile(llvm::StringRef file_path) const override;

  /* lldb::TypeCategoryImplSP GetFormatters() override; */

  HardcodedFormatters::HardcodedSyntheticFinder
  GetHardcodedSynthetics() override;

  HardcodedFormatters::HardcodedSummaryFinder
  GetHardcodedSummaries() override;

  bool SymbolNameFitsToLanguage(Mangled mangled) const override;

};

} // namespace lldb_private

#endif // LLDB_SOURCE_PLUGINS_LANGUAGE_D_DLANGUAGE_H
