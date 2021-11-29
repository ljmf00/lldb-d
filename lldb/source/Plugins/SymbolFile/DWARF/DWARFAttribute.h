//===-- DWARFAttribute.h ----------------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLDB_SOURCE_PLUGINS_SYMBOLFILE_DWARF_DWARFATTRIBUTE_H
#define LLDB_SOURCE_PLUGINS_SYMBOLFILE_DWARF_DWARFATTRIBUTE_H

#include "DWARFDIE.h"
#include "DWARFDefines.h"
#include "DWARFFormValue.h"
#include "lldb/Core/Declaration.h"
#include "lldb/Utility/ConstString.h"
#include "llvm/ADT/SmallVector.h"
#include <vector>

class DWARFUnit;

class DWARFAttribute {
public:
  DWARFAttribute(dw_attr_t attr, dw_form_t form,
                 DWARFFormValue::ValueType value)
      : m_attr(attr), m_form(form), m_value(value) {}

  dw_attr_t get_attr() const { return m_attr; }
  dw_form_t get_form() const { return m_form; }
  DWARFFormValue::ValueType get_value() const { return m_value; }
  void get(dw_attr_t &attr, dw_form_t &form,
           DWARFFormValue::ValueType &val) const {
    attr = m_attr;
    form = m_form;
    val = m_value;
  }
  typedef std::vector<DWARFAttribute> collection;
  typedef collection::iterator iterator;
  typedef collection::const_iterator const_iterator;

protected:
  dw_attr_t m_attr;
  dw_form_t m_form;
  DWARFFormValue::ValueType m_value;
};

class DWARFAttributes {
public:
  DWARFAttributes();
  ~DWARFAttributes();

  void Append(const DWARFFormValue &form_value, dw_offset_t attr_die_offset,
              dw_attr_t attr);
  DWARFUnit *CompileUnitAtIndex(uint32_t i) const { return m_infos[i].cu; }
  dw_offset_t DIEOffsetAtIndex(uint32_t i) const {
    return m_infos[i].die_offset;
  }
  dw_attr_t AttributeAtIndex(uint32_t i) const {
    return m_infos[i].attr.get_attr();
  }
  dw_attr_t FormAtIndex(uint32_t i) const { return m_infos[i].attr.get_form(); }
  DWARFFormValue::ValueType ValueAtIndex(uint32_t i) const {
    return m_infos[i].attr.get_value();
  }
  bool ExtractFormValueAtIndex(uint32_t i, DWARFFormValue &form_value) const;
  DWARFDIE FormValueAsReferenceAtIndex(uint32_t i) const;
  DWARFDIE FormValueAsReference(dw_attr_t attr) const;
  uint32_t FindAttributeIndex(dw_attr_t attr) const;
  void Clear() { m_infos.clear(); }
  size_t Size() const { return m_infos.size(); }

protected:
  struct AttributeValue {
    DWARFUnit *cu; // Keep the compile unit with each attribute in
                   // case we have DW_FORM_ref_addr values
    dw_offset_t die_offset;
    DWARFAttribute attr;
  };
  typedef llvm::SmallVector<AttributeValue, 8> collection;
  collection m_infos;
};

FLAGS_ENUM(DWARFAttributeFlags)
{
  /// Whether it is an artificially generated symbol.
  eDWARFAttributeIsArtificial = (1u << 0),
  eDWARFAttributeIsExplicit = (1u << 1),
  eDWARFAttributeIsForwardDecl = (1u << 2),
  eDWARFAttributeIsInline = (1u << 3),
  eDWARFAttributeIsScopedEnum = (1u << 4),
  eDWARFAttributeIsVector = (1u << 5),
  eDWARFAttributeIsVirtual = (1u << 6),
  eDWARFAttributeIsExternal = (1u << 7),
  eDWARFAttributeExportSymbols = (1u << 8),
  eDWARFAttributeIsObjCDirect = (1u << 9),
  eDWARFAttributeIsObjCCompleteType = (1u << 10),
};

/// Parsed form of all attributes that are relevant for type reconstruction.
/// Some attributes are relevant for all kinds of types (declaration), while
/// others are only meaningful to a specific type (is_virtual).
struct ParsedDWARFTypeAttributes {
  explicit ParsedDWARFTypeAttributes(const DWARFDIE &die);

  lldb::AccessType accessibility = lldb::eAccessNone;
  uint32_t attr_flags = 0;
  const char *mangled_name = nullptr;
  lldb_private::ConstString name;
  lldb_private::Declaration decl;
  DWARFDIE object_pointer;
  DWARFFormValue abstract_origin;
  DWARFFormValue containing_type;
  DWARFFormValue signature;
  DWARFFormValue specification;
  DWARFFormValue type;
  lldb::LanguageType class_language = lldb::eLanguageTypeUnknown;
  llvm::Optional<uint64_t> byte_size;
  size_t calling_convention = llvm::dwarf::DW_CC_normal;
  uint32_t bit_stride = 0;
  uint32_t byte_stride = 0;
  uint32_t encoding = 0;

  bool is_artificial() const {
    return attr_flags & eDWARFAttributeIsArtificial;
  }
  bool is_explicit() const {
    return attr_flags & eDWARFAttributeIsExplicit;
  }
  bool is_forward_declaration() const {
    return attr_flags & eDWARFAttributeIsForwardDecl;
  }
  bool is_inline() const {
    return attr_flags & eDWARFAttributeIsInline;
  }
  bool is_scoped_enum() const {
    return attr_flags &eDWARFAttributeIsScopedEnum;
  }
  bool is_vector() const {
    return attr_flags & eDWARFAttributeIsVector;
  }
  bool is_virtual() const {
    return attr_flags & eDWARFAttributeIsVirtual;
  }
  bool is_external() const {
    return attr_flags & eDWARFAttributeIsExternal;
  }
  bool exports_symbols() const {
    return attr_flags & eDWARFAttributeExportSymbols;
  }
  bool is_objc_direct_call() const {
    return attr_flags & eDWARFAttributeIsObjCDirect;
  }
  bool is_objc_complete_type() const {
    return attr_flags & eDWARFAttributeIsObjCCompleteType;
  }
};

#endif // LLDB_SOURCE_PLUGINS_SYMBOLFILE_DWARF_DWARFATTRIBUTE_H
