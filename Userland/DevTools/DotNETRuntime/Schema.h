/*
 * Copyright (c) 2021, Daniel Flaws <dflaws1@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#pragma once

#include "Enums.h"
#include "Forward.h"
#include "TableIndex.h"
#include <AK/ByteBuffer.h>
#include <AK/String.h>

namespace DotNETRuntime {
struct SchemaUtils {
    static ColumnValue coded_idx(CodedIndexId id);

    static ColumnValue table(TableId id);

    static void init_schema();
    static Vector<Column> const& table_columns(TableId id);
};

namespace Schema {
struct Assembly {
    int HashAlgId;
    int MajorVersion;
    int MinorVersion;
    int BuildNumber;
    int RevisionNumber;
    int Flags;
    int PublicKey;
    int Name;
    int Culture;

    static Vector<Column> Columns;
};

struct AssemblyOS {
    int OSPlatformId;
    int OSMajorVersion;
    int OSMinorVersion;

    static Vector<Column> Columns;
};

struct AssemblyProcessor {
    int Processor;
    static Vector<Column> Columns;
};

struct AssemblyRef {
    explicit AssemblyRef(Vector<TableCell> row);

    short MajorVersion;
    short MinorVersion;
    short BuildNumber;
    short RevisionNumber;
    int Flags;
    ByteBuffer PublicKeyOrToken;
    String Name;
    String Culture;
    ByteBuffer HashValue;
    static Vector<Column> Columns;
};

struct AssemblyRefOS {
    int OSPlatformId;
    int OSMajorVersion;
    int OSMinorVersion;
    int AssemblyRef;
    static Vector<Column> Columns;
};

struct AssemblyRefProcessor {
    int Processor;
    int AssemblyRef;
    static Vector<Column> Columns;
};

struct ClassLayout {
    int PackingSize;
    int ClassSize;
    int Parent;
    static Vector<Column> Columns;
};

struct Constant {
    int Type;
    int Parent;
    int Value;
    static Vector<Column> Columns;
};

struct CustomAttribute {
    int Parent;
    int Type;
    int Value;
    static Vector<Column> Columns;
};

struct DeclSecurity {
    int Action;
    int Parent;
    int PermissionSet;
    static Vector<Column> Columns;
};

struct EventMap {
    int Parent;
    int EventList;
    static Vector<Column> Columns;
};

struct Event {
    int EventFlags;
    int Name;
    int EventType;
    static Vector<Column> Columns;
};

struct ExportedType {
    int Flags;
    int TypeDefId;
    int TypeName;
    int TypeNamespace;
    int Implementation;
    static Vector<Column> Columns;
};

struct Field {
    explicit Field(Vector<TableCell> row);

    short Flags;
    String Name;
    ByteBuffer Signature;
    static Vector<Column> Columns;
};

struct FieldLayout {
    int Offset;
    int Field;
    static Vector<Column> Columns;
};

struct FieldMarshal {
    int Parent;
    int NativeType;
    static Vector<Column> Columns;
};

struct FieldRVA {
    int RVA;
    int Field;
    static Vector<Column> Columns;
};

struct File {
    int Flags;
    int Name;
    int HashValue;
    static Vector<Column> Columns;
};

struct GenericParam {
    int Number;
    int Flags;
    int Owner;
    int Name;
    static Vector<Column> Columns;
};

struct GenericParamConstraint {
    int Owner;
    int Constraint;
    static Vector<Column> Columns;
};

struct ImplMap {
    int MappingFlags;
    int MemberForwarded;
    int ImportName;
    int ImportScope;
    static Vector<Column> Columns;
};

struct InterfaceImpl {
    int Class;
    int Interface;
    static Vector<Column> Columns;
};

struct ManifestResource {
    int Offset;
    int Flags;
    int Name;
    int Implementation;
    static Vector<Column> Columns;
};

struct MemberRef {
    explicit MemberRef(Vector<TableCell> row);

    TableIndex Class;
    String Name;
    ByteBuffer Signature;
    static Vector<Column> Columns;
};

struct MethodDef {
    explicit MethodDef(Vector<TableCell> row);

    int RVA;
    short ImplFlags;
    short Flags;
    String Name;
    ByteBuffer Signature;
    TableIndex ParamList;
    static Vector<Column> Columns;
};

struct MethodImpl {
    int Class;
    int MethodBody;
    int MethodDeclaration;
    static Vector<Column> Columns;
};

struct MethodSemantics {
    int Semantics;
    int Method;
    int Association;
    static Vector<Column> Columns;
};

struct MethodSpec {
    int Method;
    int Instantiation;
    static Vector<Column> Columns;
};

struct Module {
    int Generation;
    int Name;
    int Mvid;
    int EncId;
    int EncBaseId;
    static Vector<Column> Columns;
};

struct ModuleRef {
    int Name;
    static Vector<Column> Columns;
};

struct NestedClass {
    int Class;
    int EnclosingClass;
    static Vector<Column> Columns;
};

struct Param {
    int Flags;
    int Sequence;
    int Name;
    static Vector<Column> Columns;
};

struct Property {
    int Flags;
    int Name;
    int Type;
    static Vector<Column> Columns;
};

struct PropertyMap {
    int Parent;
    int PropertyList;
    static Vector<Column> Columns;
};

struct StandAloneSig {
    explicit StandAloneSig(Vector<TableCell> row);

    ByteBuffer Signature;
    static Vector<Column> Columns;
};

struct TypeDef {
    TypeDef() { }
    explicit TypeDef(Vector<TableCell> row);

    int Flags;
    String TypeName;
    String TypeNamespace;
    TableIndex Extends;
    TableIndex FieldList;
    TableIndex MethodList;
    static Vector<Column> Columns;
};

struct TypeRef {
    explicit TypeRef(Vector<TableCell> row);

    TableIndex ResolutionScope;
    String TypeName;
    String TypeNamespace;
    static Vector<Column> Columns;
};

struct TypeSpec {
    explicit TypeSpec(Vector<TableCell> row);

    ByteBuffer Signature;
    static Vector<Column> Columns;
};

struct FieldPtr {
    int Field;
    static Vector<Column> Columns;
};

struct MethodPtr {
    int Method;
    static Vector<Column> Columns;
};

struct ParamPtr {
    int Param;
    static Vector<Column> Columns;
};

struct EventPtr {
    int Event;
    static Vector<Column> Columns;
};

struct PropertyPtr {
    int Property;
    static Vector<Column> Columns;
};

struct EncodingLog {
    int Token;
    int FuncCode;
    static Vector<Column> Columns;
};

struct EncodingMap {
    int Token;
    static Vector<Column> Columns;
};
}
}