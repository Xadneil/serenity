/*
 * Copyright (c) 2021, Daniel Flaws <dflaws1@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#include "MetadataReader.h"
#include "LocalVar.h"
#include "MethodDef.h"
#include "MethodSignature.h"
#include "Schema.h"

namespace DotNETRuntime {
DotNETRuntime::MethodDef MetadataReader::make_method(Schema::MethodDef const& schema_method_def)
{
    auto signature = TypeSignature::decode_method_signature(schema_method_def.Signature);
    Optional<MethodBody> body;
    Vector<LocalVar> local_vars;
    if (schema_method_def.RVA != 0) {
        body = read_body_at(schema_method_def.RVA);
        local_vars = resolve_local_vars(body->local_sig);
    } else if ((schema_method_def.ImplFlags & (int)MethodImplAttributes::InternalCall) != 0) {
        warnln("encountered unimplemented internal method. {}, 0x{:08x}, 0x{:08x}", schema_method_def.Name, schema_method_def.Flags, schema_method_def.ImplFlags);
        VERIFY_NOT_REACHED();
    } else {
        warnln("encountered method without body. {}, 0x{:08x}, 0x{:08x}", schema_method_def.Name, schema_method_def.Flags, schema_method_def.ImplFlags);
        VERIFY_NOT_REACHED();
    }
    DotNETRuntime::MethodDef method_def {
        .rva = (unsigned)schema_method_def.RVA,
        .name = schema_method_def.Name,
        .flags = schema_method_def.Flags,
        .signature = signature,
        .body = body,
        .local_vars = local_vars,
    };

    return method_def;
}

Vector<LocalVar> MetadataReader::resolve_local_vars(u32 token)
{
    if (token == 0)
        return {};
    static HashMap<u32, Vector<LocalVar>> cache;
    auto cache_iterator = cache.find(token);
    if (cache_iterator != cache.end())
        return cache_iterator->value;
    auto t = CodedIndex::decode_table_index(token);
    auto row = read_row(t);
    Schema::StandAloneSig stand_alone_sig(row);
    InputMemoryStream reader { stand_alone_sig.Signature };
    auto prolog = IO::read_packed_int(reader);
    if (prolog != (u32)SignatureKind::LocalVars) {
        warnln("Invalid local variable signature");
        VERIFY_NOT_REACHED();
    }
    auto count = IO::read_packed_int(reader);
    Vector<LocalVar> vars;
    for (size_t i = 0; i < count; i++) {
        auto type = TypeSignature::decode_type_signature(reader);
        auto name = String::formatted("v{}", i);
        vars.append(LocalVar {
            .index = i,
            .type = type,
            .name = name });
    }
    cache.set(token, vars);
    return vars;
}

MethodDef MetadataReader::read_entry_point()
{
    auto table_index = CodedIndex::decode_table_index(m_image.entry_point_token);
    if (table_index.table == TableId::MethodDef)
        return make_method(Schema::MethodDef { read_row(table_index) });
    else {
        warnln("read_entry_point returned no method. Actually got a {}", table_id_to_string(table_index.table));
        return {};
    }
}
}
