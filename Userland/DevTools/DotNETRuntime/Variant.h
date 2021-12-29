/*
 * Copyright (c) 2021, Daniel Flaws <dflaws1@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "Enums.h"
#include "Forward.h"
#include <AK/Variant.h>

namespace DotNETRuntime {
using CLIVariant = AK::Variant<Empty, bool, u8, i8, u16, i16, u32, i32, u64, i64, float, double, Object*, void*>;

static CLIVariant null_variant { (Object*)nullptr };

struct CLIVariantUtils {
    static CLIVariant init_zeroed(ElementType element_type);
};

}
