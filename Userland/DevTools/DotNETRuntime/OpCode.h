/*
 * Copyright (c) 2021, Daniel Flaws <dflaws1@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#pragma once

#include "Enums.h"
#include <AK/Types.h>

namespace DotNETRuntime {
enum class StackBehavior {
    Pop0 = 0,
    Pop1 = 1,
    Pop1_pop1 = 2,
    Popi = 3,
    Popi_pop1 = 4,
    Popi_popi = 5,
    Popi_popi8 = 6,
    Popi_popi_popi = 7,
    Popi_popr4 = 8,
    Popi_popr8 = 9,
    Popref = 10,
    Popref_pop1 = 11,
    Popref_popi = 12,
    Popref_popi_popi = 13,
    Popref_popi_popi8 = 14,
    Popref_popi_popr4 = 15,
    Popref_popi_popr8 = 16,
    Popref_popi_popref = 17,
    Push0 = 18,
    Push1 = 19,
    Push1_push1 = 20,
    Pushi = 21,
    Pushi8 = 22,
    Pushr4 = 23,
    Pushr8 = 24,
    Pushref = 25,
    Varpop = 26,
    Varpush = 27,
    Popref_popi_pop1 = 28,
};

enum class OperandType {
    InlineBrTarget = 0,
    InlineField = 1,
    InlineI = 2,
    InlineI8 = 3,
    InlineMethod = 4,
    InlineNone = 5,
    InlineR = 7,
    InlineSig = 9,
    InlineString = 10,
    InlineSwitch = 11,
    InlineTok = 12,
    InlineType = 13,
    InlineVar = 14,
    ShortInlineBrTarget = 15,
    ShortInlineI = 16,
    ShortInlineR = 17,
    ShortInlineVar = 18,
};

enum class OpCodeType {
    Macro = 1,
    Nternal = 2,
    Objmodel = 3,
    Prefix = 4,
    Primitive = 5,
};

enum class FlowControl {
    Branch = 0,
    Break = 1,
    Call = 2,
    Cond_Branch = 3,
    Meta = 4,
    Next = 5,
    Return = 7,
    Throw = 8,
};

class OpCode {
public:
    StackBehavior stack_behavior_pop() const { return (StackBehavior)((m_flags >> StackBehaviorPopShift) & StackBehaviorMask); }
    StackBehavior stack_behavior_push() const { return (StackBehavior)((m_flags >> StackBehaviorPushShift) & StackBehaviorMask); }
    OperandType operand_type() const { return (OperandType)(m_flags & OperandTypeMask); }
    OpCodeType op_code_type() const { return (OpCodeType)((m_flags >> OpCodeTypeShift) & OpCodeTypeMask); }
    int size() const { return (m_flags >> SizeShift) & SizeMask; }
    i16 value() const { return (short)m_value; }
    FlowControl flow_control() const { return (FlowControl)((m_flags >> FlowControlShift) & FlowControlMask); }
    bool ends_unconditional_jmp_blk() const { return (m_flags & EndsUncondJmpBlkFlag) != 0; }
    int stack_change() const { return (m_flags >> StackChangeShift); }

    OpCode(InstructionCode value, u32 flags)
        : m_value(value)
        , m_flags(flags)
    {
    }

    static constexpr int OperandTypeMask = 0x1F;
    static constexpr int FlowControlShift = 5;
    static constexpr int FlowControlMask = 0x0F;
    static constexpr int OpCodeTypeShift = 9;
    static constexpr int OpCodeTypeMask = 0x07;
    static constexpr int StackBehaviorPopShift = 12;
    static constexpr int StackBehaviorPushShift = 17;
    static constexpr int StackBehaviorMask = 0x1F;
    static constexpr int SizeShift = 22;
    static constexpr int SizeMask = 0x03;
    static constexpr int EndsUncondJmpBlkFlag = 0x01000000;
    static constexpr int StackChangeShift = 28;

private:
    InstructionCode m_value { InstructionCode::Nop };
    u32 m_flags { 0 };
};
}
