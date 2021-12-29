/*
 * Copyright (c) 2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <Userland/DevTools/DotNETRuntime/Heap/Heap.h>

namespace DotNETRuntime {

class DeferGC {
public:
    explicit DeferGC(Heap& heap)
        : m_heap(heap)
    {
        m_heap.defer_gc({});
    }

    ~DeferGC()
    {
        m_heap.undefer_gc({});
    }

private:
    Heap& m_heap;
};

}
