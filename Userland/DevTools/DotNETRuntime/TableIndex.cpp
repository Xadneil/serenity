/*
 * Copyright (c) 2021, Daniel Flaws <dflaws1@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#include "TableIndex.h"
#include "MetadataReader.h"
#include "Signature.h"

namespace DotNETRuntime {
String TableIndex::dump(MetadataReader& meta) const
{
    String extra;
    if (index_plus_one > 0) {
        switch (table) {
        case TableId::TypeSpec: {
            extra = TypeSignature::decode_type_signature(Schema::TypeSpec(meta.read_row(*this)).Signature)->dump(meta);
            break;
        }
        default:
            break;
        }
    }
    if (extra.is_empty())
        return String::formatted("{}[{}]", table_id_to_string(table), index_plus_one);
    return String::formatted("{}[{}] {}", table_id_to_string(table), index_plus_one, extra);
}
}
