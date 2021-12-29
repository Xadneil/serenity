/*
 * Copyright (c) 2021, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/Vector.h>
#include <Userland/DevTools/DotNETRuntime/Forward.h>

namespace DotNETRuntime {

class BlockAllocator {
public:
    BlockAllocator();
    ~BlockAllocator();

    void* allocate_block(char const* name);
    void deallocate_block(void*);

private:
    static constexpr size_t max_cached_blocks = 512;

    Vector<void*, max_cached_blocks> m_blocks;
};

}
