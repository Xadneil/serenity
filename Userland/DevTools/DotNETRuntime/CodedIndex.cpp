/*
 * Copyright (c) 2021, Daniel Flaws <dflaws1@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#include "CodedIndex.h"
#include "MetadataReader.h"
#include "Schema.h"
#include "Signature.h"
#include "Types.h"
#include <AK/String.h>

namespace DotNETRuntime {

HashMap<int, CodedIndex> s_coded_index_map;

HashMap<int, CodedIndex> const& CodedIndex::coded_index_map()
{
    return s_coded_index_map;
}

void CodedIndex::init_coded_indexes()
{
    s_coded_index_map.set(
        (int)CodedIndexId::CustomAttributeType,
        CodedIndex(
            CodedIndexId::CustomAttributeType,
            3,
            std::initializer_list<TableId> {
                TableId::TypeRef,
                TableId::TypeRef,
                TableId::MethodDef,
                TableId::MemberRef,
                TableId::TypeDef,
            }));
    s_coded_index_map.set(
        (int)CodedIndexId::HasConstant,
        CodedIndex(
            CodedIndexId::HasConstant,
            2,
            std::initializer_list<TableId> {
                TableId::Field,
                TableId::Param,
                TableId::Property,
            }));
    s_coded_index_map.set(
        (int)CodedIndexId::HasCustomAttribute,
        CodedIndex(
            CodedIndexId::HasCustomAttribute,
            5,
            std::initializer_list<TableId> {
                TableId::MethodDef,
                TableId::Field,
                TableId::TypeRef,
                TableId::TypeDef,
                TableId::Param,
                TableId::InterfaceImpl,
                TableId::MemberRef,
                TableId::Module,
                TableId::DeclSecurity,
                TableId::Property,
                TableId::Event,
                TableId::StandAloneSig,
                TableId::ModuleRef,
                TableId::TypeSpec,
                TableId::Assembly,
                TableId::AssemblyRef,
                TableId::File,
                TableId::ExportedType,
                TableId::ManifestResource,
                TableId::GenericParam,
            }));
    s_coded_index_map.set(
        (int)CodedIndexId::HasDeclSecurity,
        CodedIndex(
            CodedIndexId::HasDeclSecurity,
            2,
            std::initializer_list<TableId> {
                TableId::TypeDef,
                TableId::MethodDef,
                TableId::Assembly,
            }));
    s_coded_index_map.set(
        (int)CodedIndexId::HasFieldMarshal,
        CodedIndex(
            CodedIndexId::HasFieldMarshal,
            1,
            std::initializer_list<TableId> {
                TableId::Field,
                TableId::Param,
            }));
    s_coded_index_map.set(
        (int)CodedIndexId::HasSemantics,
        CodedIndex(
            CodedIndexId::HasSemantics,
            1,
            std::initializer_list<TableId> {
                TableId::Event,
                TableId::Property,
            }));
    s_coded_index_map.set(
        (int)CodedIndexId::Implementation,
        CodedIndex(
            CodedIndexId::Implementation,
            2,
            std::initializer_list<TableId> {
                TableId::File,
                TableId::AssemblyRef,
                TableId::ExportedType,
            }));
    s_coded_index_map.set(
        (int)CodedIndexId::MemberForwarded,
        CodedIndex(
            CodedIndexId::MemberForwarded,
            1,
            std::initializer_list<TableId> {
                TableId::Field,
                TableId::MethodDef,
            }));
    s_coded_index_map.set(
        (int)CodedIndexId::MemberRefParent,
        CodedIndex(
            CodedIndexId::MemberRefParent,
            3,
            std::initializer_list<TableId> {
                TableId::TypeDef,
                TableId::TypeRef,
                TableId::ModuleRef,
                TableId::MethodDef,
                TableId::TypeSpec,
            }));
    s_coded_index_map.set(
        (int)CodedIndexId::MethodDefOrRef,
        CodedIndex(
            CodedIndexId::MethodDefOrRef,
            1,
            std::initializer_list<TableId> {
                TableId::MethodDef,
                TableId::MemberRef,
            }));
    s_coded_index_map.set(
        (int)CodedIndexId::ResolutionScope,
        CodedIndex(
            CodedIndexId::ResolutionScope,
            2,
            std::initializer_list<TableId> {
                TableId::Module,
                TableId::ModuleRef,
                TableId::AssemblyRef,
                TableId::TypeRef,
            }));
    s_coded_index_map.set(
        (int)CodedIndexId::TypeDefOrRef,
        CodedIndex(
            CodedIndexId::TypeDefOrRef,
            2,
            std::initializer_list<TableId> {
                TableId::TypeDef,
                TableId::TypeRef,
                TableId::TypeSpec,
            }));
    s_coded_index_map.set(
        (int)CodedIndexId::TypeOrMethodDef,
        CodedIndex(
            CodedIndexId::TypeOrMethodDef,
            1,
            std::initializer_list<TableId> {
                TableId::TypeDef,
                TableId::MethodDef,
            }));
};

}