//===-- DFormatterFunctions.cpp -------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "DFormatterFunctions.h"
#include "DTypeUtils.h"

#include "lldb/Utility/ConstString.h"
#include "lldb/DataFormatters/FormatClasses.h"
#include "lldb/DataFormatters/FormattersHelpers.h"
#include "lldb/DataFormatters/StringPrinter.h"

using namespace lldb_private;
using namespace lldb_private::formatters;
using namespace lldb;

/* DStringSliceSummaryProvider */

namespace {
class DSliceSyntheticFrontEnd : public SyntheticChildrenFrontEnd {
public:
  DSliceSyntheticFrontEnd(ValueObject &valobj)
      : SyntheticChildrenFrontEnd(valobj) {
    Update();
  }

  ~DSliceSyntheticFrontEnd() override = default;

  size_t CalculateNumChildren() override { return m_len; }

  lldb::ValueObjectSP GetChildAtIndex(size_t idx) override {
    if (idx < m_len) {
      ValueObjectSP &cached = m_children[idx];
      if (!cached) {
        StreamString idx_name;
        idx_name.Printf("[%" PRIu64 "]", (uint64_t)idx);
        lldb::addr_t object_at_idx = m_base_data_address;
        object_at_idx += idx * m_type.GetByteSize(nullptr).getValueOr(1);
        cached = CreateValueObjectFromAddress(
            idx_name.GetString(), object_at_idx,
            m_backend.GetExecutionContextRef(), m_type);
      }
      return cached;
    }
    return ValueObjectSP();
  }

  bool Update() override {
    size_t old_count = m_len;

    if (!IsDSlice(m_backend, &m_type, &m_base_data_address, &m_len))
      return old_count == 0;

    m_children.clear(); // ptr
    m_children.clear(); // length

    return old_count == m_len;
  }

  bool MightHaveChildren() override { return true; }

  size_t GetIndexOfChildWithName(ConstString name) override {
    return ExtractIndexFromString(name.AsCString());
  }

private:
  CompilerType m_type;
  lldb::addr_t m_base_data_address;
  uint64_t m_len;
  std::map<size_t, lldb::ValueObjectSP> m_children;
};

} // end of anonymous namespace

SyntheticChildrenFrontEnd * lldb_private::formatters::DSliceSyntheticFrontEndCreator(
    CXXSyntheticChildren *, lldb::ValueObjectSP valobj_sp) {
  if (!valobj_sp)
    return nullptr;

  lldb::ProcessSP process_sp(valobj_sp->GetProcessSP());
  if (!process_sp)
    return nullptr;
  return new DSliceSyntheticFrontEnd(*valobj_sp);
}

bool lldb_private::formatters::DStringSliceSummaryProvider(
    ValueObject &valobj, Stream &stream, const TypeSummaryOptions &) {
  DataExtractor data;
  Status error;
  valobj.GetData(data, error);

  if (error.Fail())
    return false;

  CompilerType Type;
  addr_t AddrData;
  uint64_t Len;
  // is a D slice for sure, just fetching values
  IsDSlice(valobj, &Type, &AddrData, &Len);

  TargetSP target_sp = valobj.GetTargetSP();
  if (!target_sp)
    return false;

  StringPrinter::ReadStringAndDumpToStreamOptions options(valobj);
  options.SetLocation(AddrData);
  options.SetTargetSP(target_sp);
  options.SetStream(&stream);
  options.SetQuote('"');
  options.SetNeedsZeroTermination(false);
  options.SetBinaryZeroIsTerminator(true);
  options.SetSourceSize(Len);
  options.SetHasSourceSize(true);

  llvm::Optional<uint64_t> SizeOpt = Type.GetByteSize(nullptr);
  uint64_t ByteSize = SizeOpt.hasValue() ? *SizeOpt : 1;

  switch (ByteSize) {
  case 1:
    return StringPrinter::ReadStringAndDumpToStream<
        StringPrinter::StringElementType::UTF8>(options);
  case 2:
    options.SetSuffixToken("w");
    return StringPrinter::ReadStringAndDumpToStream<
        StringPrinter::StringElementType::UTF16>(options);
  case 4:
    options.SetSuffixToken("d");
    return StringPrinter::ReadStringAndDumpToStream<
        StringPrinter::StringElementType::UTF32>(options);
  default:
    stream.Printf("size for string element is not valid");
    return true;
  }
  return true;
}
