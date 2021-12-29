/*
 * Copyright (c) 2021, Daniel Flaws <dflaws1@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#pragma once

#include "LocalVar.h"
#include "MethodBody.h"
#include "MethodSignature.h"
#include <AK/String.h>

namespace DotNETRuntime {
struct MethodDef {
    unsigned rva { 0 };
    String name;
    int flags;
    MethodSignature signature;
    Optional<MethodBody> body;
    Vector<LocalVar> local_vars;
    ~MethodDef();
};
}
