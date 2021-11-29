//===-- DWARFASTParserD.cpp -----------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "DWARFASTParserD.h"
#include "Plugins/TypeSystem/D/TypeSystemD.h"

using namespace lldb_private;
using namespace lldb;

DWARFASTParserD::DWARFASTParserD(TypeSystemD &ast)
	: m_ast(ast) {}

TypeSP DWARFASTParserD::ParseTypeFromDWARF(const SymbolContext &sc,
                                        const DWARFDIE &die,
                                        bool *type_is_new_ptr)
{
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
