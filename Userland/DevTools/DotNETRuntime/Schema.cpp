/*
 * Copyright (c) 2021, Daniel Flaws <dflaws1@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#include "Schema.h"
#include "CodedIndex.h"
#include "Types.h"

namespace DotNETRuntime {
namespace Schema {
ColumnValue s_int32 { ColumnType::Int32, 0 };
ColumnValue s_int16 { (short)0 };
ColumnValue s_str { ColumnType::StringIndex, 0 };
ColumnValue s_blob { ColumnType::BlobIndex, 0 };

AssemblyRef::AssemblyRef(Vector<TableCell> row)
    : MajorVersion(row[0].int16())
    , MinorVersion(row[1].int16())
    , BuildNumber(row[2].int16())
    , RevisionNumber(row[3].int16())
    , Flags(row[4].int32())
    , PublicKeyOrToken(row[5].blob())
    , Name(row[6].string())
    , Culture(row[7].string())
    , HashValue(row[8].blob())
{
}

MemberRef::MemberRef(Vector<TableCell> row)
    : Class(row[0].table())
    , Name(row[1].string())
    , Signature(row[2].blob())
{
}

MethodDef::MethodDef(Vector<TableCell> row)
    : RVA(row[0].int32())
    , ImplFlags(row[1].int16())
    , Flags(row[2].int16())
    , Name(row[3].string())
    , Signature(row[4].blob())
    , ParamList(row[5].table())
{
}

StandAloneSig::StandAloneSig(Vector<TableCell> row)
    : Signature(row[0].blob())
{
}

TypeRef::TypeRef(Vector<TableCell> row)
    : ResolutionScope(row[0].table())
    , TypeName(row[1].string())
    , TypeNamespace(row[2].string())
{
}

TypeSpec::TypeSpec(Vector<TableCell> row)
    : Signature(row[0].blob())
{
}

TypeDef::TypeDef(Vector<TableCell> row)
    : Flags(row[0].int32())
    , TypeName(row[1].string())
    , TypeNamespace(row[2].string())
    , Extends(row[3].table())
    , FieldList(row[4].table())
    , MethodList(row[5].table())
{
}

Field::Field(Vector<TableCell> row)
    : Flags(row[0].int16())
    , Name(row[1].string())
    , Signature(row[2].blob())
{
}
}

ColumnValue SchemaUtils::coded_idx(CodedIndexId id)
{
    auto& map = CodedIndex::coded_index_map();
    auto option = map.find((int)id);
    if (option == map.end()) {
        warnln("Coded Index {} not implemented.", (int)id);
        VERIFY_NOT_REACHED();
    }
    return ColumnValue { option->value };
}

ColumnValue SchemaUtils::table(TableId id)
{
    return ColumnValue { TableIndex {
        .table = id,
        .index_plus_one = 0,
    } };
}

using namespace Schema;
void SchemaUtils::init_schema()
{

    Assembly::Columns = { {
                              .index = 0,
                              .name = "HashAlgId",
                              .value = s_int32,
                          },
        {
            .index = 1,
            .name = "MajorVersion",
            .value = s_int16,
        },
        {
            .index = 2,
            .name = "MinorVersion",
            .value = s_int16,
        },
        {
            .index = 3,
            .name = "BuildNumber",
            .value = s_int16,
        },
        {
            .index = 4,
            .name = "RevisionNumber",
            .value = s_int16,
        },
        {
            .index = 5,
            .name = "Flags",
            .value = s_int32,
        },
        {
            .index = 6,
            .name = "PublicKey",
            .value = s_blob,
        },
        {
            .index = 7,
            .name = "Name",
            .value = s_str,
        },
        {
            .index = 8,
            .name = "Culture",
            .value = s_str,
        } };

    AssemblyOS::Columns = { {
                                .index = 0,
                                .name = "OSPlatformId",
                                .value = s_int32,
                            },
        {
            .index = 1,
            .name = "OSMajorVersion",
            .value = s_int32,
        },
        {
            .index = 2,
            .name = "OSMinorVersion",
            .value = s_int32,
        } };

    AssemblyProcessor::Columns = { {
        .index = 0,
        .name = "Processor",
        .value = s_int32,
    } };

    AssemblyRef::Columns = { {
                                 .index = 0,
                                 .name = "MajorVersion",
                                 .value = s_int16,
                             },
        {
            .index = 1,
            .name = "MinorVersion",
            .value = s_int16,
        },
        {
            .index = 2,
            .name = "BuildNumber",
            .value = s_int16,
        },
        {
            .index = 3,
            .name = "RevisionNumber",
            .value = s_int16,
        },
        {
            .index = 4,
            .name = "Flags",
            .value = s_int32,
        },
        {
            .index = 5,
            .name = "PublicKeyOrToken",
            .value = s_blob,
        },
        {
            .index = 6,
            .name = "Name",
            .value = s_str,
        },
        {
            .index = 7,
            .name = "Culture",
            .value = s_str,
        },
        {
            .index = 8,
            .name = "HashValue",
            .value = s_blob,
        } };

    AssemblyRefOS::Columns = { {
                                   .index = 0,
                                   .name = "OSPlatformId",
                                   .value = s_int32,
                               },
        {
            .index = 1,
            .name = "OSMajorVersion",
            .value = s_int32,
        },
        {
            .index = 2,
            .name = "OSMinorVersion",
            .value = s_int32,
        },
        {
            .index = 3,
            .name = "AssemblyRef",
            .value = table(TableId::AssemblyRef),
        } };

    AssemblyRefProcessor::Columns = { {
                                          .index = 0,
                                          .name = "Processor",
                                          .value = s_int32,
                                      },
        {
            .index = 1,
            .name = "AssemblyRef",
            .value = table(TableId::AssemblyRef),
        } };

    ClassLayout::Columns = { {
                                 .index = 0,
                                 .name = "PackingSize",
                                 .value = s_int16,
                             },
        {
            .index = 1,
            .name = "ClassSize",
            .value = s_int32,
        },
        {
            .index = 2,
            .name = "Parent",
            .value = table(TableId::TypeDef),
        } };

    Constant::Columns = { {
                              .index = 0,
                              .name = "Type",
                              .value = s_int16,
                          },
        {
            .index = 1,
            .name = "Parent",
            .value = coded_idx(CodedIndexId::HasConstant),
        },
        {
            .index = 2,
            .name = "Value",
            .value = s_blob,
        } };

    CustomAttribute::Columns = { {
                                     .index = 0,
                                     .name = "Parent",
                                     .value = coded_idx(CodedIndexId::HasCustomAttribute),
                                 },
        {
            .index = 1,
            .name = "Type",
            .value = coded_idx(CodedIndexId::CustomAttributeType),
        },
        {
            .index = 2,
            .name = "Value",
            .value = s_blob,
        } };

    DeclSecurity::Columns = { {
                                  .index = 0,
                                  .name = "Action",
                                  .value = s_int16,
                              },
        {
            .index = 1,
            .name = "Parent",
            .value = coded_idx(CodedIndexId::HasDeclSecurity),
        },
        {
            .index = 2,
            .name = "PermissionSet",
            .value = s_blob,
        } };

    EventMap::Columns = { {
                              .index = 0,
                              .name = "Parent",
                              .value = table(TableId::TypeDef),
                          },
        {
            .index = 1,
            .name = "EventList",
            .value = table(TableId::Event),
        } };

    Event::Columns = { {
                           .index = 0,
                           .name = "EventFlags",
                           .value = s_int16,
                       },
        {
            .index = 1,
            .name = "Name",
            .value = s_str,
        },
        {
            .index = 2,
            .name = "EventType",
            .value = coded_idx(CodedIndexId::TypeDefOrRef),
        } };

    ExportedType::Columns = { {
                                  .index = 0,
                                  .name = "Flags",
                                  .value = s_int32,
                              },
        {
            .index = 1,
            .name = "TypeDefId",
            .value = s_int32,
        },
        {
            .index = 2,
            .name = "TypeName",
            .value = s_str,
        },
        {
            .index = 3,
            .name = "TypeNamespace",
            .value = s_str,
        },
        {
            .index = 4,
            .name = "Implementation",
            .value = coded_idx(CodedIndexId::Implementation),
        } };

    Field::Columns = { {
                           .index = 0,
                           .name = "Flags",
                           .value = s_int16,
                       },
        {
            .index = 1,
            .name = "Name",
            .value = s_str,
        },
        {
            .index = 2,
            .name = "Signature",
            .value = s_blob,
        } };

    FieldLayout::Columns = { {
                                 .index = 0,
                                 .name = "Offset",
                                 .value = s_int32,
                             },
        {
            .index = 1,
            .name = "Field",
            .value = table(TableId::Field),
        } };

    FieldMarshal::Columns = { {
                                  .index = 0,
                                  .name = "Parent",
                                  .value = coded_idx(CodedIndexId::HasFieldMarshal),
                              },
        {
            .index = 1,
            .name = "NativeType",
            .value = s_blob,
        } };

    FieldRVA::Columns = { {
                              .index = 0,
                              .name = "RVA",
                              .value = s_int32,
                          },
        {
            .index = 1,
            .name = "Field",
            .value = table(TableId::Field),
        } };

    File::Columns = { {
                          .index = 0,
                          .name = "Flags",
                          .value = s_int32,
                      },
        {
            .index = 1,
            .name = "Name",
            .value = s_str,
        },
        {
            .index = 2,
            .name = "HashValue",
            .value = s_blob,
        } };

    GenericParam::Columns = { {
                                  .index = 0,
                                  .name = "Number",
                                  .value = s_int16,
                              },
        {
            .index = 1,
            .name = "Flags",
            .value = s_int16,
        },
        {
            .index = 2,
            .name = "Owner",
            .value = coded_idx(CodedIndexId::TypeOrMethodDef),
        },
        {
            .index = 3,
            .name = "Name",
            .value = s_str,
        } };

    GenericParamConstraint::Columns = { {
                                            .index = 0,
                                            .name = "Owner",
                                            .value = table(TableId::GenericParam),
                                        },
        {
            .index = 1,
            .name = "Constraint",
            .value = coded_idx(CodedIndexId::TypeDefOrRef),
        } };

    ImplMap::Columns = { {
                             .index = 0,
                             .name = "MappingFlags",
                             .value = s_int16,
                         },
        {
            .index = 1,
            .name = "MemberForwarded",
            .value = coded_idx(CodedIndexId::MemberForwarded),
        },
        {
            .index = 2,
            .name = "ImportName",
            .value = s_str,
        },
        {
            .index = 3,
            .name = "ImportScope",
            .value = table(TableId::ModuleRef),
        } };

    InterfaceImpl::Columns = { {
                                   .index = 0,
                                   .name = "Class",
                                   .value = table(TableId::TypeDef),
                               },
        {
            .index = 1,
            .name = "Interface",
            .value = coded_idx(CodedIndexId::TypeDefOrRef),
        } };

    ManifestResource::Columns = { {
                                      .index = 0,
                                      .name = "Offset",
                                      .value = s_int32,
                                  },
        {
            .index = 1,
            .name = "Flags",
            .value = s_int32,
        },
        {
            .index = 2,
            .name = "Name",
            .value = s_str,
        },
        {
            .index = 3,
            .name = "Implementation",
            .value = coded_idx(CodedIndexId::Implementation),
        } };

    MemberRef::Columns = { {
                               .index = 0,
                               .name = "Class",
                               .value = coded_idx(CodedIndexId::MemberRefParent),
                           },
        {
            .index = 1,
            .name = "Name",
            .value = s_str,
        },
        {
            .index = 2,
            .name = "Signature",
            .value = s_blob,
        } };

    Schema::MethodDef::Columns = { {
                                       .index = 0,
                                       .name = "RVA",
                                       .value = s_int32,
                                   },
        {
            .index = 1,
            .name = "ImplFlags",
            .value = s_int16,
        },
        {
            .index = 2,
            .name = "Flags",
            .value = s_int16,
        },
        {
            .index = 3,
            .name = "Name",
            .value = s_str,
        },
        {
            .index = 4,
            .name = "Signature",
            .value = s_blob,
        },
        {
            .index = 5,
            .name = "ParamList",
            .value = table(TableId::Param),
        } };

    MethodImpl::Columns = { {
                                .index = 0,
                                .name = "Class",
                                .value = table(TableId::TypeDef),
                            },
        {
            .index = 1,
            .name = "MethodBody",
            .value = coded_idx(CodedIndexId::MethodDefOrRef),
        },
        {
            .index = 2,
            .name = "MethodDeclaration",
            .value = coded_idx(CodedIndexId::MethodDefOrRef),
        } };

    MethodSemantics::Columns = { {
                                     .index = 0,
                                     .name = "Semantics",
                                     .value = s_int16,
                                 },
        {
            .index = 1,
            .name = "Method",
            .value = table(TableId::MethodDef),
        },
        {
            .index = 2,
            .name = "Association",
            .value = coded_idx(CodedIndexId::HasSemantics),
        } };

    MethodSpec::Columns = { {
                                .index = 0,
                                .name = "Method",
                                .value = coded_idx(CodedIndexId::MethodDefOrRef),
                            },
        {
            .index = 1,
            .name = "Instantiation",
            .value = s_blob,
        } };

    Module::Columns = { {
                            .index = 0,
                            .name = "Generation",
                            .value = s_int16,
                        },
        {
            .index = 1,
            .name = "Name",
            .value = s_str,
        },
        {
            .index = 2,
            .name = "Mvid",
            .value = ColumnValue { ColumnType::GuidIndex, 0 },
        },
        {
            .index = 3,
            .name = "EncId",
            .value = ColumnValue { ColumnType::GuidIndex, 0 },
        },
        {
            .index = 4,
            .name = "EncBaseId",
            .value = ColumnValue { ColumnType::GuidIndex, 0 },
        } };

    ModuleRef::Columns = { {
        .index = 0,
        .name = "Name",
        .value = s_str,
    } };

    NestedClass::Columns = { {
                                 .index = 0,
                                 .name = "Class",
                                 .value = table(TableId::TypeDef),
                             },
        {
            .index = 1,
            .name = "EnclosingClass",
            .value = table(TableId::TypeDef),
        } };

    Param::Columns = { {
                           .index = 0,
                           .name = "Flags",
                           .value = s_int16,
                       },
        {
            .index = 1,
            .name = "Sequence",
            .value = s_int16,
        },
        {
            .index = 2,
            .name = "Name",
            .value = s_str,
        } };

    Property::Columns = { {
                              .index = 0,
                              .name = "Flags",
                              .value = s_int16,
                          },
        {
            .index = 1,
            .name = "Name",
            .value = s_str,
        },
        {
            .index = 2,
            .name = "Type",
            .value = s_blob,
        } };

    PropertyMap::Columns = { {
                                 .index = 0,
                                 .name = "Parent",
                                 .value = table(TableId::TypeDef),
                             },
        {
            .index = 1,
            .name = "PropertyList",
            .value = table(TableId::Property),
        } };

    StandAloneSig::Columns = { {
        .index = 0,
        .name = "Signature",
        .value = s_blob,
    } };

    TypeDef::Columns = { {
                             .index = 0,
                             .name = "Flags",
                             .value = s_int32,
                         },
        {
            .index = 1,
            .name = "TypeName",
            .value = s_str,
        },
        {
            .index = 2,
            .name = "TypeNamespace",
            .value = s_str,
        },
        {
            .index = 3,
            .name = "Extends",
            .value = coded_idx(CodedIndexId::TypeDefOrRef),
        },
        {
            .index = 4,
            .name = "FieldList",
            .value = table(TableId::Field),
        },
        {
            .index = 5,
            .name = "MethodList",
            .value = table(TableId::MethodDef),
        } };

    TypeRef::Columns = { {
                             .index = 0,
                             .name = "ResolutionScope",
                             .value = coded_idx(CodedIndexId::ResolutionScope),
                         },
        {
            .index = 1,
            .name = "TypeName",
            .value = s_str,
        },
        {
            .index = 2,
            .name = "TypeNamespace",
            .value = s_str,
        } };

    TypeSpec::Columns = { {
        .index = 0,
        .name = "Signature",
        .value = s_blob,
    } };

    FieldPtr::Columns = { {
        .index = 0,
        .name = "Field",
        .value = table(TableId::Field),
    } };

    MethodPtr::Columns = { {
        .index = 0,
        .name = "Method",
        .value = table(TableId::MethodDef),
    } };

    ParamPtr::Columns = { {
        .index = 0,
        .name = "Param",
        .value = table(TableId::Param),
    } };

    EventPtr::Columns = { {
        .index = 0,
        .name = "Event",
        .value = table(TableId::Event),
    } };

    PropertyPtr::Columns = { {
        .index = 0,
        .name = "Property",
        .value = table(TableId::Property),
    } };

    EncodingLog::Columns = { {
                                 .index = 0,
                                 .name = "Token",
                                 .value = s_int32,
                             },
        {
            .index = 1,
            .name = "FuncCode",
            .value = s_int32,
        } };

    EncodingMap::Columns = { {
        .index = 0,
        .name = "Token",
        .value = s_int32,
    } };
}

Vector<Column> const& SchemaUtils::table_columns(TableId id)
{
    switch (id) {
#define __ENUMERATE_TABLE_ID(name, id, snake) \
    case TableId::name:                       \
        return Schema::name::Columns;
        ENUMERATE_TABLE_IDS
#undef __ENUMERATE_TABLE_ID
    default:
        warnln("No table columns for {}", table_id_to_string(id));
        VERIFY_NOT_REACHED();
    }
}

#define __ENUMERATE_TABLE_ID(name, id, snake) \
    Vector<Column> Schema::name::Columns = {};
ENUMERATE_TABLE_IDS
#undef __ENUMERATE_TABLE_ID
}