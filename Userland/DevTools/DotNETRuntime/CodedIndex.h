/*
 * Copyright (c) 2021, Daniel Flaws <dflaws1@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#pragma once

#include "Enums.h"
#include "Forward.h"
#include "TableIndex.h"
#include <AK/Assertions.h>
#include <AK/String.h>
#include <AK/Vector.h>

namespace DotNETRuntime {

struct CodedIndex {
    CodedIndex(CodedIndexId id, int bits, Vector<TableId> const& tables)
        : id(id)
        , bits(bits)
        , tables(move(tables))
    {
    }
    CodedIndexId id { CodedIndexId::Invalid };
    int bits { 0 };
    Vector<TableId> tables;

    static void init_coded_indexes();

    static TableIndex decode_coded_index(CodedIndex const& coded_index, u32 value)
    {
        u32 mask = (0xFF >> (8 - coded_index.bits));
        int tag = value & mask;
        if (tag < 0 || (size_t)tag >= coded_index.tables.size())
            VERIFY_NOT_REACHED();
        int index = value >> coded_index.bits;
        return {
            .table = coded_index.tables[tag],
            .index_plus_one = index
        };
    }

    static HashMap<int, CodedIndex> const& coded_index_map();

    static TableIndex decode_table_index(u32 token)
    {
        auto id = (token >> 24) & (u32)0xFF;
        int index = token & (u32)0xFFFFFF;
        return {
            .table = (TableId)id,
            .index_plus_one = index
        };
    }
};
}
