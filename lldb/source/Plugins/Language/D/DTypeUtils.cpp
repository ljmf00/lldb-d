//===-- DTypeUtils.cpp ------------------------------------------*---------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "DTypeUtils.h"

#include "lldb/Symbol/CompilerType.h"
#include "lldb/Utility/ConstString.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/StringSwitch.h"

using namespace lldb;
using namespace llvm;

namespace lldb_private {

bool IsDSlice(ValueObject &Valobj, CompilerType* Type, addr_t* AddrData,
              uint64_t* Len)
{
  if (Valobj.MightHaveChildren())
      {
        size_t nchildren = Valobj.GetNumChildren();

        // doesn't have exactly two childrens
        if (nchildren != 2)
          return false;

        ConstString ptr_name("ptr");
        ConstString length_name("length");

        // fetch slice fields
        ValueObjectSP ptr_sp = Valobj.GetChildMemberWithName(ptr_name, true);
        ValueObjectSP length_sp = Valobj.GetChildMemberWithName(length_name, true);

        // doesn't have those two exact childrens
        if (!ptr_sp || !length_sp)
          return false;

        CompilerType PteType = ptr_sp->GetCompilerType().GetPointeeType();
        // isn't a pointer
        if (!PteType.IsValid())
          return false;

        bool success;
        uint64_t lenVal = length_sp->GetValueAsUnsigned(0, &success);
        // can't fetch unsigned value
        if (!success)
          return false;

        if (Type != nullptr)
          *Type = PteType;
        if (AddrData != nullptr)
          *AddrData = ptr_sp->GetPointerValue();
        if (Len != nullptr)
          *Len = lenVal;

        return true;
      }
      return false;
}

bool IsDStringSlice(ValueObject &Valobj, CompilerType* Type, addr_t* AddrData,
                    uint64_t* Len)
{
  CompilerType TypeRet;
  bool IsSlice = IsDSlice(Valobj, &TypeRet, AddrData, Len);
  if (!IsSlice)
    return false;

  if (Type != nullptr)
    *Type = TypeRet;

  return IsCharType(TypeRet);
}

bool IsCharType(CompilerType Type)
{
  switch(Type.GetFormat())
  {
    case eFormatUnicode8:
    case eFormatUnicode16:
    case eFormatUnicode32:
    case eFormatChar:
    case eFormatCharPrintable:
      return true;
    case eFormatInvalid: break;
    default:
      return false;
  }

  // fallback to char type names if no proper enconding found
  return StringSwitch<bool>(Type.GetDisplayTypeName().GetCString())
    .Cases(
        "char", "char8_t",   // UTF-8
        "wchar", "char16_t", // UTF-16
        "dchar", "char32_t", // UTF-32
        "wchar_t",           // platform dependent
        true)
    .Default(false);
}

} // namespace lldb_private
