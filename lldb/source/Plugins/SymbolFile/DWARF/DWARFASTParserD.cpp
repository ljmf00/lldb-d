//===-- DWARFASTParserD.cpp -----------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "DWARFASTParserD.h"
#include "DWARFASTParserClang.h"
#include "DWARFDebugInfo.h"
#include "DWARFDeclContext.h"
#include "DWARFDefines.h"
#include "SymbolFileDWARF.h"
#include "SymbolFileDWARFDebugMap.h"
#include "SymbolFileDWARFDwo.h"
#include "UniqueDWARFASTType.h"

#include "Plugins/TypeSystem/D/TypeSystemD.h"

using namespace lldb_private;
using namespace lldb;

DWARFASTParserD::DWARFASTParserD(TypeSystemD &ast)
	: m_ast(ast) {}

TypeSP DWARFASTParserD::ParseTypeFromDWARF(const SymbolContext &sc,
                                        const DWARFDIE &die,
                                        bool *type_is_new_ptr)
{
  if (type_is_new_ptr)
    *type_is_new_ptr = false;

  if (!die)
    return nullptr;

  // TODO: Add logging

  SymbolFileDWARF *dwarf = die.GetDWARF();

  Type *type_ptr = dwarf->GetDIEToType().lookup(die.GetDIE());
  if (type_ptr == DIE_IS_BEING_PARSED)
    return nullptr;

  if (type_ptr)
    return type_ptr->shared_from_this();
  // Set a bit that lets us know that we are currently parsing this
  dwarf->GetDIEToType()[die.GetDIE()] = DIE_IS_BEING_PARSED;

  ParsedDWARFTypeAttributes attrs(die);

  if (DWARFDIE signature_die = attrs.signature.Reference()) {
    if (TypeSP type_sp =
            ParseTypeFromDWARF(sc, signature_die, type_is_new_ptr)) {
      dwarf->GetDIEToType()[die.GetDIE()] = type_sp.get();
      return type_sp;
    }
    return nullptr;
  }

  if (type_is_new_ptr)
    *type_is_new_ptr = true;

  const dw_tag_t tag = die.Tag();

  TypeSP type_sp;
  switch(tag) {
    case DW_TAG_typedef:
    case DW_TAG_base_type:
    case DW_TAG_pointer_type:
    case DW_TAG_reference_type:
    case DW_TAG_rvalue_reference_type:
    case DW_TAG_const_type:
    case DW_TAG_restrict_type:
    case DW_TAG_volatile_type:
    case DW_TAG_atomic_type:
    case DW_TAG_unspecified_type:
      return TypeSP();
      break;

    default: break;
  }

  // TODO: Use Update Symbol function
  return TypeSP();
}

Function *
DWARFASTParserD::ParseFunctionFromDWARF(CompileUnit &comp_unit,
                       const DWARFDIE &die,
                       const AddressRange &range)
{
  return nullptr;
}

bool
DWARFASTParserD::CompleteTypeFromDWARF(const DWARFDIE &die, Type *type,
                      lldb_private::CompilerType &compiler_type)
{
  return false;
}

CompilerDecl
DWARFASTParserD::GetDeclForUIDFromDWARF(const DWARFDIE &die)
{
  return CompilerDecl();
}

CompilerDeclContext
DWARFASTParserD::GetDeclContextForUIDFromDWARF(const DWARFDIE &die)
{
  return CompilerDeclContext();
}

CompilerDeclContext
DWARFASTParserD::GetDeclContextContainingUIDFromDWARF(const DWARFDIE &die)
{
  return CompilerDeclContext();
}

void DWARFASTParserD::EnsureAllDIEsInDeclContextHaveBeenParsed(
    lldb_private::CompilerDeclContext decl_context) {}
