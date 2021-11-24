#include "TypeSystemD.h"
#include "lldb/lldb-enumerations.h"

#include "lldb/Core/Module.h"
#include "lldb/Core/PluginManager.h"
#include "lldb/Symbol/Type.h"
#include "lldb/Utility/ArchSpec.h"

LLDB_PLUGIN_DEFINE(TypeSystemD)

namespace lldb_private {

// LLVM RTTI support
char TypeSystemD::ID;

TypeSystemD::TypeSystemD() = default;

TypeSystemD::~TypeSystemD() { Finalize(); }
void TypeSystemD::Finalize() {}

void TypeSystemD::Initialize() {
  PluginManager::RegisterPlugin(
      GetPluginNameStatic(), "D base AST context plug-in", CreateInstance,
      GetSupportedLanguages(), GetSupportedLanguages());
}

void TypeSystemD::Terminate() {
  PluginManager::UnregisterPlugin(CreateInstance);
}

LanguageSet TypeSystemD::GetSupportedLanguages() {
  LanguageSet languages;
  languages.Insert(lldb::eLanguageTypeD);
  return languages;
}

lldb::LanguageType
TypeSystemD::GetMinimumLanguage(lldb::opaque_compiler_type_t /*unused*/) {
  return lldb::eLanguageTypeD;
}

bool TypeSystemD::SupportsLanguage(lldb::LanguageType language) {
  return language == lldb::eLanguageTypeD;
}

lldb::TypeSystemSP TypeSystemD::CreateInstance(lldb::LanguageType language,
                                               Module *module, Target *target) {
  if (language != lldb::eLanguageTypeD)
    return lldb::TypeSystemSP();

  ArchSpec arch;
  if (module)
    arch = module->GetArchitecture();
  else if (target)
    arch = target->GetArchitecture();

  if (!arch.IsValid())
    return lldb::TypeSystemSP();

  if (module)
    return std::shared_ptr<TypeSystemD>(new TypeSystemD);

  return lldb::TypeSystemSP();
}

#ifndef NDEBUG
LLVM_DUMP_METHOD void
TypeSystemD::dump(lldb::opaque_compiler_type_t type) const {}

bool TypeSystemD::Verify(lldb::opaque_compiler_type_t type) { return !type; }
#endif

void TypeSystemD::Dump(llvm::raw_ostream &output) {}

void TypeSystemD::DumpValue(lldb::opaque_compiler_type_t type,
                            ExecutionContext *exe_ctx, Stream *s,
                            lldb::Format format, const DataExtractor &data,
                            lldb::offset_t data_offset, size_t data_byte_size,
                            uint32_t bitfield_bit_size,
                            uint32_t bitfield_bit_offset, bool show_types,
                            bool show_summary, bool verbose, uint32_t depth) {}

bool TypeSystemD::DumpTypeValue(lldb::opaque_compiler_type_t type, Stream *s,
                                lldb::Format format, const DataExtractor &data,
                                lldb::offset_t data_offset,
                                size_t data_byte_size,
                                uint32_t bitfield_bit_size,
                                uint32_t bitfield_bit_offset,
                                ExecutionContextScope *exe_scope) {
  return false;
}

void TypeSystemD::DumpSummary(lldb::opaque_compiler_type_t type,
                              ExecutionContext *exe_ctx, Stream *s,
                              const DataExtractor &data,
                              lldb::offset_t data_offset,
                              size_t data_byte_size) {}

void TypeSystemD::DumpTypeDescription(lldb::opaque_compiler_type_t type,
                                      lldb::DescriptionLevel level) {}

void TypeSystemD::DumpTypeDescription(lldb::opaque_compiler_type_t type,
                                      Stream *s, lldb::DescriptionLevel level) {
}

bool TypeSystemD::IsVectorType(lldb::opaque_compiler_type_t type,
                               CompilerType *element_type, uint64_t *size) {
  return false;
}

uint32_t TypeSystemD::IsHomogeneousAggregate(lldb::opaque_compiler_type_t type,
                                             CompilerType *base_type_ptr) {
  return 0;
}

bool TypeSystemD::IsReferenceType(lldb::opaque_compiler_type_t type,
                                  CompilerType *pointee_type, bool *is_rvalue) {
  return false;
}

bool TypeSystemD::IsPossibleDynamicType(
    lldb::opaque_compiler_type_t type,
    CompilerType *target_type, // Can pass nullptr
    bool check_cplusplus, bool check_objc) {
  return false;
}

bool TypeSystemD::IsRuntimeGeneratedType(lldb::opaque_compiler_type_t type) {
  return false;
}

bool TypeSystemD::IsPointerType(lldb::opaque_compiler_type_t type,
                                CompilerType *pointee_type) {
  return false;
}

bool TypeSystemD::IsPointerOrReferenceType(lldb::opaque_compiler_type_t type,
                                           CompilerType *pointee_type) {
  return false;
}
bool TypeSystemD::IsArrayType(lldb::opaque_compiler_type_t type,
                              CompilerType *element_type, uint64_t *size,
                              bool *is_incomplete) {
  return false;
}

bool TypeSystemD::IsAggregateType(lldb::opaque_compiler_type_t type) {
  return false;
}

bool TypeSystemD::IsAnonymousType(lldb::opaque_compiler_type_t type) {
  return false;
}

bool TypeSystemD::IsBeingDefined(lldb::opaque_compiler_type_t type) {
  return false;
}

bool TypeSystemD::IsCharType(lldb::opaque_compiler_type_t type) {
  return false;
}

bool TypeSystemD::IsCompleteType(lldb::opaque_compiler_type_t type) {
  return false;
}

bool TypeSystemD::IsConst(lldb::opaque_compiler_type_t type) { return false; }

bool TypeSystemD::IsCStringType(lldb::opaque_compiler_type_t type,
                                uint32_t &length) {
  return false;
}

bool TypeSystemD::IsTypedefType(lldb::opaque_compiler_type_t type) {
  return false;
}

bool TypeSystemD::IsPolymorphicClass(lldb::opaque_compiler_type_t type) {
  return false;
}

bool TypeSystemD::IsFunctionPointerType(lldb::opaque_compiler_type_t type) {
  return false;
}

bool TypeSystemD::IsBlockPointerType(lldb::opaque_compiler_type_t type,
                                     CompilerType *function_pointer_type_ptr) {
  return false;
}

bool TypeSystemD::IsIntegerType(lldb::opaque_compiler_type_t type,
                                bool &is_signed) {
  return false;
}

bool TypeSystemD::IsEnumerationType(lldb::opaque_compiler_type_t type,
                                    bool &is_signed) {
  return false;
}

bool TypeSystemD::IsScopedEnumerationType(lldb::opaque_compiler_type_t type) {
  return false;
}

uint32_t IsHomogeneousAggregate(lldb::opaque_compiler_type_t type,
                                CompilerType *base_type_ptr) {
  return 0;
}

bool TypeSystemD::IsScalarType(lldb::opaque_compiler_type_t type) {
  return false;
}

bool TypeSystemD::IsFunctionType(lldb::opaque_compiler_type_t type) {
  return false;
}

bool TypeSystemD::IsVoidType(lldb::opaque_compiler_type_t type) {
  return false;
}

bool TypeSystemD::IsDefined(lldb::opaque_compiler_type_t type) { return false; }

bool TypeSystemD::IsFloatingPointType(lldb::opaque_compiler_type_t type,
                                      uint32_t &count, bool &is_complex) {
  return false;
}

bool TypeSystemD::CanPassInRegisters(const CompilerType &type) { return false; }

void TypeSystemD::ForEachEnumerator(
    lldb::opaque_compiler_type_t type,
    std::function<bool(const CompilerType &integer_type, ConstString name,
                       const llvm::APSInt &value)> const &callback) {}

CompilerType TypeSystemD::GetTypedefedType(lldb::opaque_compiler_type_t type) {
  return CompilerType();
}

CompilerType
TypeSystemD::GetBuiltinTypeForEncodingAndBitSize(lldb::Encoding encoding,
                                                 size_t bit_size) {
  return CompilerType();
}

CompilerType TypeSystemD::GetBasicTypeFromAST(lldb::BasicType basic_type) {
  return CompilerType();
}

llvm::Optional<uint64_t>
TypeSystemD::GetBitSize(lldb::opaque_compiler_type_t type,
                        ExecutionContextScope *exe_scope) {
  return llvm::None;
}

lldb::Encoding TypeSystemD::GetEncoding(lldb::opaque_compiler_type_t type,
                                        uint64_t &count) {
  return lldb::eEncodingInvalid;
}

lldb::Format TypeSystemD::GetFormat(lldb::opaque_compiler_type_t type) {
  return lldb::eFormatDefault;
}

lldb::TypeClass TypeSystemD::GetTypeClass(lldb::opaque_compiler_type_t type) {
  return lldb::eTypeClassInvalid;
}

unsigned TypeSystemD::GetTypeQualifiers(lldb::opaque_compiler_type_t type) {
  return 0;
}

CompilerType TypeSystemD::GetTypeForDecl(void *opaque_decl) {
  return CompilerType();
}

CompilerType TypeSystemD::GetChildCompilerTypeAtIndex(
    lldb::opaque_compiler_type_t type, ExecutionContext *exe_ctx, size_t idx,
    bool transparent_pointers, bool omit_empty_base_classes,
    bool ignore_array_bounds, std::string &child_name,
    uint32_t &child_byte_size, int32_t &child_byte_offset,
    uint32_t &child_bitfield_bit_size, uint32_t &child_bitfield_bit_offset,
    bool &child_is_base_class, bool &child_is_deref_of_parent,
    ValueObject *valobj, uint64_t &language_flags) {
  return CompilerType();
}

uint32_t TypeSystemD::GetNumFields(lldb::opaque_compiler_type_t type) {
  return 0;
}

CompilerType TypeSystemD::GetFieldAtIndex(lldb::opaque_compiler_type_t type,
                                          size_t idx, std::string &name,
                                          uint64_t *bit_offset_ptr,
                                          uint32_t *bitfield_bit_size_ptr,
                                          bool *is_bitfield_ptr) {
  return CompilerType();
}

uint32_t
TypeSystemD::GetNumDirectBaseClasses(lldb::opaque_compiler_type_t type) {
  return 0;
}

uint32_t
TypeSystemD::GetNumVirtualBaseClasses(lldb::opaque_compiler_type_t type) {
  return 0;
}

CompilerType
TypeSystemD::GetDirectBaseClassAtIndex(lldb::opaque_compiler_type_t type,
                                       size_t idx, uint32_t *bit_offset_ptr) {
  return CompilerType();
}

CompilerType
TypeSystemD::GetVirtualBaseClassAtIndex(lldb::opaque_compiler_type_t type,
                                        size_t idx, uint32_t *bit_offset_ptr) {
  return CompilerType();
}

uint32_t TypeSystemD::GetIndexOfChildWithName(lldb::opaque_compiler_type_t type,
                                              const char *name,
                                              bool omit_empty_base_classes) {
  return 0;
}

size_t TypeSystemD::GetIndexOfChildMemberWithName(
    lldb::opaque_compiler_type_t type, const char *name,
    bool omit_empty_base_classes, std::vector<uint32_t> &child_indexes) {
  return 0;
}

size_t TypeSystemD::GetNumTemplateArguments(lldb::opaque_compiler_type_t type) {
  return 0;
}

lldb::TemplateArgumentKind
TypeSystemD::GetTemplateArgumentKind(lldb::opaque_compiler_type_t type,
                                     size_t idx) {
  return lldb::eTemplateArgumentKindNull;
}
CompilerType
TypeSystemD::GetTypeTemplateArgument(lldb::opaque_compiler_type_t type,
                                     size_t idx) {
  return CompilerType();
}
llvm::Optional<CompilerType::IntegralTemplateArgument>
TypeSystemD::GetIntegralTemplateArgument(lldb::opaque_compiler_type_t type,
                                         size_t idx) {
  return llvm::None;
}

CompilerType TypeSystemD::GetTypeForFormatters(void *type) {
  return CompilerType();
}

llvm::Optional<size_t>
TypeSystemD::GetTypeBitAlign(lldb::opaque_compiler_type_t type,
                             ExecutionContextScope *exe_scope) {
  return llvm::None;
}

uint32_t TypeSystemD::GetNumChildren(lldb::opaque_compiler_type_t type,
                                     bool omit_empty_base_classes,
                                     const ExecutionContext *exe_ctx) {
  return 0;
}

CompilerType TypeSystemD::GetBuiltinTypeByName(ConstString name) {
  return CompilerType();
}

lldb::BasicType
TypeSystemD::GetBasicTypeEnumeration(lldb::opaque_compiler_type_t type) {
  return lldb::eBasicTypeInvalid;
}

CompilerType
TypeSystemD::GetArrayElementType(lldb::opaque_compiler_type_t type,
                                 ExecutionContextScope *exe_scope) {
  return CompilerType();
}

CompilerType TypeSystemD::GetArrayType(lldb::opaque_compiler_type_t type,
                                       uint64_t size) {
  return CompilerType();
}

CompilerType TypeSystemD::GetCanonicalType(lldb::opaque_compiler_type_t type) {
  return CompilerType();
}

CompilerType
TypeSystemD::GetFullyUnqualifiedType(lldb::opaque_compiler_type_t type) {
  return CompilerType();
}

CompilerType
TypeSystemD::GetEnumerationIntegerType(lldb::opaque_compiler_type_t type) {
  return CompilerType();
}

// Returns -1 if this isn't a function of if the function doesn't have a
// prototype Returns a value >= 0 if there is a prototype.
int TypeSystemD::GetFunctionArgumentCount(lldb::opaque_compiler_type_t type) {
  return -1;
}

CompilerType
TypeSystemD::GetFunctionArgumentTypeAtIndex(lldb::opaque_compiler_type_t type,
                                            size_t idx) {
  return CompilerType();
}

CompilerType
TypeSystemD::GetFunctionReturnType(lldb::opaque_compiler_type_t type) {
  return CompilerType();
}

size_t TypeSystemD::GetNumMemberFunctions(lldb::opaque_compiler_type_t type) {
  return 0;
}

TypeMemberFunctionImpl
TypeSystemD::GetMemberFunctionAtIndex(lldb::opaque_compiler_type_t type,
                                      size_t idx) {
  return TypeMemberFunctionImpl();
}

CompilerType
TypeSystemD::GetNonReferenceType(lldb::opaque_compiler_type_t type) {
  return CompilerType();
}

CompilerType TypeSystemD::GetPointeeType(lldb::opaque_compiler_type_t type) {
  return CompilerType();
}

CompilerType TypeSystemD::GetPointerType(lldb::opaque_compiler_type_t type) {
  return CompilerType();
}

CompilerType
TypeSystemD::GetLValueReferenceType(lldb::opaque_compiler_type_t type) {
  return CompilerType();
}

CompilerType
TypeSystemD::GetRValueReferenceType(lldb::opaque_compiler_type_t type) {
  return CompilerType();
}

CompilerType TypeSystemD::GetAtomicType(lldb::opaque_compiler_type_t type) {
  return CompilerType();
}

CompilerType TypeSystemD::AddConstModifier(lldb::opaque_compiler_type_t type) {
  return CompilerType();
}

CompilerType
TypeSystemD::AddVolatileModifier(lldb::opaque_compiler_type_t type) {
  return CompilerType();
}

CompilerType
TypeSystemD::AddRestrictModifier(lldb::opaque_compiler_type_t type) {
  return CompilerType();
}

const llvm::fltSemantics &TypeSystemD::GetFloatTypeSemantics(size_t byte_size) {
  return llvm::APFloatBase::Bogus();
}

bool TypeSystemD::GetCompleteType(lldb::opaque_compiler_type_t type) {
  return false;
}

ConstString TypeSystemD::GetTypeName(lldb::opaque_compiler_type_t type) {
  return ConstString();
}

ConstString TypeSystemD::GetDisplayTypeName(lldb::opaque_compiler_type_t type) {
  return ConstString();
}

uint32_t
TypeSystemD::GetTypeInfo(lldb::opaque_compiler_type_t type,
                         CompilerType *pointee_or_element_compiler_type) {
  return 0;
}

uint32_t TypeSystemD::GetPointerByteSize() { return 0; }

size_t
TypeSystemD::GetNumberOfFunctionArguments(lldb::opaque_compiler_type_t type) {
  return 0;
}

CompilerType
TypeSystemD::GetFunctionArgumentAtIndex(lldb::opaque_compiler_type_t type,
                                        const size_t index) {
  return CompilerType();
}

ConstString TypeSystemD::DeclGetName(void *opaque_decl) {
  return ConstString();
}

std::vector<CompilerDecl>
TypeSystemD::DeclContextFindDeclByName(void *opaque_decl_ctx, ConstString name,
                                       const bool ignore_using_decls) {
  return std::vector<CompilerDecl>();
}

ConstString TypeSystemD::DeclContextGetName(void *opaque_decl_ctx) {
  return ConstString();
}

ConstString
TypeSystemD::DeclContextGetScopeQualifiedName(void *opaque_decl_ctx) {
  return ConstString();
}

bool TypeSystemD::DeclContextIsClassMethod(
    void *opaque_decl_ctx, lldb::LanguageType *language_ptr,
    bool *is_instance_method_ptr, ConstString *language_object_name_ptr) {
  return false;
}

bool TypeSystemD::DeclContextIsContainedInLookup(void *opaque_decl_ctx,
                                                 void *other_opaque_decl_ctx) {
  return false;
}

} // namespace lldb_private
