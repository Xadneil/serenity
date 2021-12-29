/*
 * Copyright (c) 2021, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <Userland/DevTools/DotNETRuntime/Heap/Heap.h>
#include <Userland/DevTools/DotNETRuntime/Heap/MarkedVector.h>

namespace DotNETRuntime {

MarkedVectorBase::MarkedVectorBase(Heap& heap)
    : m_heap(heap)
{
    m_heap.did_create_marked_vector({}, *this);
}

MarkedVectorBase::MarkedVectorBase(MarkedVectorBase&& other)
    : m_heap(other.m_heap)
    , m_cells(move(other.m_cells))
{
    m_heap.did_create_marked_vector({}, *this);
}

MarkedVectorBase::~MarkedVectorBase()
{
    m_heap.did_destroy_marked_vector({}, *this);
}

}
