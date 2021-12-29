/*
 * Copyright (c) 2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <Userland/DevTools/DotNETRuntime/CLIInterpreter.h>
#include <Userland/DevTools/DotNETRuntime/Heap/Cell.h>
#include <Userland/DevTools/DotNETRuntime/Heap/Handle.h>
#include <Userland/DevTools/DotNETRuntime/Heap/Heap.h>

namespace DotNETRuntime {

HandleImpl::HandleImpl(Cell* cell)
    : m_cell(cell)
{
    m_cell->heap().did_create_handle({}, *this);
}

HandleImpl::~HandleImpl()
{
    m_cell->heap().did_destroy_handle({}, *this);
}

}
