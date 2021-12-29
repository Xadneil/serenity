/*
 * Copyright (c) 2021, Daniel Flaws <dflaws1@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#pragma once

#include "Signature.h"
#include <AK/String.h>

namespace DotNETRuntime {
struct LocalVar {
    u32 index { 0 };
    NonnullRefPtr<TypeSignature> type;
    String name;
};
}