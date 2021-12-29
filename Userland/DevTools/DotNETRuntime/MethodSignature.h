/*
 * Copyright (c) 2021, Daniel Flaws <dflaws1@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#pragma once

#include "Forward.h"
#include <AK/NonnullRefPtrVector.h>
#include <AK/RefPtr.h>
#include <AK/Types.h>

namespace DotNETRuntime {
struct MethodSignature {
    bool is_property { false };
    int calling_conventions { 0 };
    size_t generic_param_count { 0 };
    RefPtr<TypeSignature> return_type;
    NonnullRefPtrVector<TypeSignature> params;

    String dump(MetadataReader& meta) const;

    bool operator==(MethodSignature const& other) const;
};
}