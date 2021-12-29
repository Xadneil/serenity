/*
 * Copyright (c) 2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <AK/Badge.h>
#include <Userland/DevTools/DotNETRuntime/Heap/BlockAllocator.h>
#include <Userland/DevTools/DotNETRuntime/Heap/CellAllocator.h>
#include <Userland/DevTools/DotNETRuntime/Heap/Heap.h>
#include <Userland/DevTools/DotNETRuntime/Heap/HeapBlock.h>

namespace DotNETRuntime {

CellAllocator::CellAllocator(size_t cell_size)
    : m_cell_size(cell_size)
{
}

Cell* CellAllocator::allocate_cell(Heap& heap)
{
    if (m_usable_blocks.is_empty()) {
        auto block = HeapBlock::create_with_cell_size(heap, m_cell_size);
        m_usable_blocks.append(*block.leak_ptr());
    }

    auto& block = *m_usable_blocks.last();
    auto* cell = block.allocate();
    VERIFY(cell);
    if (block.is_full())
        m_full_blocks.append(*m_usable_blocks.last());
    return cell;
}

void CellAllocator::block_did_become_empty(Badge<Heap>, HeapBlock& block)
{
    auto& heap = block.heap();
    block.m_list_node.remove();
    // NOTE: HeapBlocks are managed by the BlockAllocator, so we don't want to `delete` the block here.
    block.~HeapBlock();
    heap.block_allocator().deallocate_block(&block);
}

void CellAllocator::block_did_become_usable(Badge<Heap>, HeapBlock& block)
{
    VERIFY(!block.is_full());
    m_usable_blocks.append(block);
}

}
