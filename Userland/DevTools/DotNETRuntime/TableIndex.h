/*
 * Copyright (c) 2021, Daniel Flaws <dflaws1@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#pragma once

#include "Enums.h"
#include "Forward.h"
#include <AK/String.h>

namespace DotNETRuntime {
struct TableIndex {
    TableId table;
    int index_plus_one { 0 };
    String dump(MetadataReader& meta) const;

    bool operator==(TableIndex const& other) const
    {
        return table == other.table && index_plus_one == other.index_plus_one;
    }
};
}