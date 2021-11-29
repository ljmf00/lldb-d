//===-- DWARFAttribute.cpp ------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "DWARFAttribute.h"
#include "DWARFASTParser.h"
#include "DWARFDebugInfo.h"
#include "DWARFUnit.h"

using namespace lldb;

DWARFAttributes::DWARFAttributes() : m_infos() {}

DWARFAttributes::~DWARFAttributes() = default;

uint32_t DWARFAttributes::FindAttributeIndex(dw_attr_t attr) const {
  collection::const_iterator end = m_infos.end();
  collection::const_iterator beg = m_infos.begin();
  collection::const_iterator pos;
  for (pos = beg; pos != end; ++pos) {
    if (pos->attr.get_attr() == attr)
      return std::distance(beg, pos);
  }
  return UINT32_MAX;
}

void DWARFAttributes::Append(const DWARFFormValue &form_value,
                             dw_offset_t attr_die_offset, dw_attr_t attr) {
  AttributeValue attr_value = {const_cast<DWARFUnit *>(form_value.GetUnit()),
                               attr_die_offset,
                               {attr, form_value.Form(), form_value.Value()}};
  m_infos.push_back(attr_value);
}

bool DWARFAttributes::ExtractFormValueAtIndex(
    uint32_t i, DWARFFormValue &form_value) const {
  const DWARFUnit *cu = CompileUnitAtIndex(i);
  form_value.SetUnit(cu);
  form_value.SetForm(FormAtIndex(i));
  if (form_value.Form() == DW_FORM_implicit_const) {
    form_value.SetValue(ValueAtIndex(i));
    return true;
  }
  lldb::offset_t offset = DIEOffsetAtIndex(i);
  return form_value.ExtractValue(cu->GetData(), &offset);
}

DWARFDIE
DWARFAttributes::FormValueAsReference(dw_attr_t attr) const {
  const uint32_t attr_idx = FindAttributeIndex(attr);
  if (attr_idx != UINT32_MAX)
    return FormValueAsReferenceAtIndex(attr_idx);
  return {};
}

DWARFDIE
DWARFAttributes::FormValueAsReferenceAtIndex(uint32_t i) const {
  DWARFFormValue form_value;
  if (ExtractFormValueAtIndex(i, form_value))
    return form_value.Reference();
  return {};
}

ParsedDWARFTypeAttributes::ParsedDWARFTypeAttributes(const DWARFDIE &die) {
  DWARFAttributes attributes;
  size_t num_attributes = die.GetAttributes(attributes);
  for (size_t i = 0; i < num_attributes; ++i) {
    dw_attr_t attr = attributes.AttributeAtIndex(i);
    DWARFFormValue form_value;
    if (!attributes.ExtractFormValueAtIndex(i, form_value))
      continue;
    switch (attr) {
    case DW_AT_abstract_origin:
      abstract_origin = form_value;
      break;

    case DW_AT_accessibility:
      accessibility = DWARFASTParser::GetAccessTypeFromDWARF(form_value.Unsigned());
      break;

    case DW_AT_artificial:
      if (form_value.Boolean())
        attr_flags |= eDWARFAttributeIsArtificial;
      break;

    case DW_AT_bit_stride:
      bit_stride = form_value.Unsigned();
      break;

    case DW_AT_byte_size:
      byte_size = form_value.Unsigned();
      break;

    case DW_AT_byte_stride:
      byte_stride = form_value.Unsigned();
      break;

    case DW_AT_calling_convention:
      calling_convention = form_value.Unsigned();
      break;

    case DW_AT_containing_type:
      containing_type = form_value;
      break;

    case DW_AT_decl_file:
      // die.GetCU() can differ if DW_AT_specification uses DW_FORM_ref_addr.
      decl.SetFile(
          attributes.CompileUnitAtIndex(i)->GetFile(form_value.Unsigned()));
      break;
    case DW_AT_decl_line:
      decl.SetLine(form_value.Unsigned());
      break;
    case DW_AT_decl_column:
      decl.SetColumn(form_value.Unsigned());
      break;

    case DW_AT_declaration:
      if (form_value.Boolean())
        attr_flags |= eDWARFAttributeIsForwardDecl;
      break;

    case DW_AT_encoding:
      encoding = form_value.Unsigned();
      break;

    case DW_AT_enum_class:
      if (form_value.Boolean())
        attr_flags |= eDWARFAttributeIsScopedEnum;
      break;

    case DW_AT_explicit:
      if (form_value.Boolean())
        attr_flags |= eDWARFAttributeIsExplicit;
      break;

    case DW_AT_external:
      if (form_value.Unsigned())
        attr_flags |= eDWARFAttributeIsExternal;
      break;

    case DW_AT_inline:
      if (form_value.Boolean())
        attr_flags |= eDWARFAttributeIsInline;
      break;

    case DW_AT_linkage_name:
    case DW_AT_MIPS_linkage_name:
      mangled_name = form_value.AsCString();
      break;

    case DW_AT_name:
      name.SetCString(form_value.AsCString());
      break;

    case DW_AT_object_pointer:
      object_pointer = form_value.Reference();
      break;

    case DW_AT_signature:
      signature = form_value;
      break;

    case DW_AT_specification:
      specification = form_value;
      break;

    case DW_AT_type:
      type = form_value;
      break;

    case DW_AT_virtuality:
      if (form_value.Unsigned())
        attr_flags |= eDWARFAttributeIsVirtual;
      break;

    case DW_AT_APPLE_objc_complete_type:
      if (form_value.Signed())
        attr_flags |= eDWARFAttributeIsObjCCompleteType;
      break;

    case DW_AT_APPLE_objc_direct:
      attr_flags |= eDWARFAttributeIsObjCDirect;
      break;

    case DW_AT_APPLE_runtime_class:
      class_language = (LanguageType)form_value.Signed();
      break;

    case DW_AT_GNU_vector:
      if (form_value.Boolean())
        attr_flags |= eDWARFAttributeIsVector;
      break;
    case DW_AT_export_symbols:
      if (form_value.Boolean())
        attr_flags |= eDWARFAttributeExportSymbols;
      break;
    }
  }
}
