/*
 * Copyright (c) 2021, Daniel Flaws <dflaws1@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "CLIInterpreter.h"

namespace DotNETRuntime {
void CLIInterpreter::gather_roots(HashTable<Cell*>& roots)
{
    for (auto& context : call_stack) {
        for (auto& argument : context.arguments) {
            if (argument.has<Object*>())
                roots.set(argument.get<Object*>());
        }
        for (auto& stack_value : context.stack) {
            if (stack_value.has<Object*>())
                roots.set(stack_value.get<Object*>());
        }
        for (auto& local : context.variables) {
            if (local.has<Object*>())
                roots.set(local.get<Object*>());
        }
    }
}
}
