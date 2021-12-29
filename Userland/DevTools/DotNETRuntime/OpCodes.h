/*
 * Copyright (c) 2021, Daniel Flaws <dflaws1@gmail::com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#pragma once

#include "OpCode.h"
#include <AK/HashMap.h>

namespace DotNETRuntime {
namespace OpCodes {

static OpCode Nop { InstructionCode::Nop,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Break { InstructionCode::Break,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Break << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Ldarg_0 { InstructionCode::Ldarg_0,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Ldarg_1 { InstructionCode::Ldarg_1,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Ldarg_2 { InstructionCode::Ldarg_2,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Ldarg_3 { InstructionCode::Ldarg_3,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Ldloc_0 { InstructionCode::Ldloc_0,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Ldloc_1 { InstructionCode::Ldloc_1,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Ldloc_2 { InstructionCode::Ldloc_2,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Ldloc_3 { InstructionCode::Ldloc_3,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Stloc_0 { InstructionCode::Stloc_0,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Stloc_1 { InstructionCode::Stloc_1,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Stloc_2 { InstructionCode::Stloc_2,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Stloc_3 { InstructionCode::Stloc_3,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Ldarg_S { InstructionCode::Ldarg_S,
    ((u32)OperandType::ShortInlineVar) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Ldarga_S { InstructionCode::Ldarga_S,
    ((u32)OperandType::ShortInlineVar) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Starg_S { InstructionCode::Starg_S,
    ((u32)OperandType::ShortInlineVar) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Ldloc_S { InstructionCode::Ldloc_S,
    ((u32)OperandType::ShortInlineVar) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Ldloca_S { InstructionCode::Ldloca_S,
    ((u32)OperandType::ShortInlineVar) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Stloc_S { InstructionCode::Stloc_S,
    ((u32)OperandType::ShortInlineVar) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Ldnull { InstructionCode::Ldnull,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushref << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Ldc_I4_M1 { InstructionCode::Ldc_I4_M1,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Ldc_I4_0 { InstructionCode::Ldc_I4_0,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Ldc_I4_1 { InstructionCode::Ldc_I4_1,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Ldc_I4_2 { InstructionCode::Ldc_I4_2,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Ldc_I4_3 { InstructionCode::Ldc_I4_3,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Ldc_I4_4 { InstructionCode::Ldc_I4_4,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Ldc_I4_5 { InstructionCode::Ldc_I4_5,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Ldc_I4_6 { InstructionCode::Ldc_I4_6,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Ldc_I4_7 { InstructionCode::Ldc_I4_7,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Ldc_I4_8 { InstructionCode::Ldc_I4_8,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Ldc_I4_S { InstructionCode::Ldc_I4_S,
    ((u32)OperandType::ShortInlineI) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Ldc_I4 { InstructionCode::Ldc_I4,
    ((u32)OperandType::InlineI) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Ldc_I8 { InstructionCode::Ldc_I8,
    ((u32)OperandType::InlineI8) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi8 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Ldc_R4 { InstructionCode::Ldc_R4,
    ((u32)OperandType::ShortInlineR) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushr4 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Ldc_R8 { InstructionCode::Ldc_R8,
    ((u32)OperandType::InlineR) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushr8 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Dup { InstructionCode::Dup,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1_push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Pop { InstructionCode::Pop,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Jmp { InstructionCode::Jmp,
    ((u32)OperandType::InlineMethod) | ((u32)FlowControl::Call << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | OpCode::EndsUncondJmpBlkFlag | (0 << OpCode::StackChangeShift) };

static OpCode Call { InstructionCode::Call,
    ((u32)OperandType::InlineMethod) | ((u32)FlowControl::Call << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Varpop << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Varpush << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Calli { InstructionCode::Calli,
    ((u32)OperandType::InlineSig) | ((u32)FlowControl::Call << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Varpop << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Varpush << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Ret { InstructionCode::Ret,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Return << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Varpop << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | OpCode::EndsUncondJmpBlkFlag | (0 << OpCode::StackChangeShift) };

static OpCode Br_S { InstructionCode::Br_S,
    ((u32)OperandType::ShortInlineBrTarget) | ((u32)FlowControl::Branch << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | OpCode::EndsUncondJmpBlkFlag | (0 << OpCode::StackChangeShift) };

static OpCode Brfalse_S { InstructionCode::Brfalse_S,
    ((u32)OperandType::ShortInlineBrTarget) | ((u32)FlowControl::Cond_Branch << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Brtrue_S { InstructionCode::Brtrue_S,
    ((u32)OperandType::ShortInlineBrTarget) | ((u32)FlowControl::Cond_Branch << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Beq_S { InstructionCode::Beq_S,
    ((u32)OperandType::ShortInlineBrTarget) | ((u32)FlowControl::Cond_Branch << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xE0000000 /*-2 << OpCode::StackChangeShift*/) };

static OpCode Bge_S { InstructionCode::Bge_S,
    ((u32)OperandType::ShortInlineBrTarget) | ((u32)FlowControl::Cond_Branch << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xE0000000 /*-2 << OpCode::StackChangeShift*/) };

static OpCode Bgt_S { InstructionCode::Bgt_S,
    ((u32)OperandType::ShortInlineBrTarget) | ((u32)FlowControl::Cond_Branch << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xE0000000 /*-2 << OpCode::StackChangeShift*/) };

static OpCode Ble_S { InstructionCode::Ble_S,
    ((u32)OperandType::ShortInlineBrTarget) | ((u32)FlowControl::Cond_Branch << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xE0000000 /*-2 << OpCode::StackChangeShift*/) };

static OpCode Blt_S { InstructionCode::Blt_S,
    ((u32)OperandType::ShortInlineBrTarget) | ((u32)FlowControl::Cond_Branch << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xE0000000 /*-2 << OpCode::StackChangeShift*/) };

static OpCode Bne_Un_S { InstructionCode::Bne_Un_S,
    ((u32)OperandType::ShortInlineBrTarget) | ((u32)FlowControl::Cond_Branch << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xE0000000 /*-2 << OpCode::StackChangeShift*/) };

static OpCode Bge_Un_S { InstructionCode::Bge_Un_S,
    ((u32)OperandType::ShortInlineBrTarget) | ((u32)FlowControl::Cond_Branch << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xE0000000 /*-2 << OpCode::StackChangeShift*/) };

static OpCode Bgt_Un_S { InstructionCode::Bgt_Un_S,
    ((u32)OperandType::ShortInlineBrTarget) | ((u32)FlowControl::Cond_Branch << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xE0000000 /*-2 << OpCode::StackChangeShift*/) };

static OpCode Ble_Un_S { InstructionCode::Ble_Un_S,
    ((u32)OperandType::ShortInlineBrTarget) | ((u32)FlowControl::Cond_Branch << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xE0000000 /*-2 << OpCode::StackChangeShift*/) };

static OpCode Blt_Un_S { InstructionCode::Blt_Un_S,
    ((u32)OperandType::ShortInlineBrTarget) | ((u32)FlowControl::Cond_Branch << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xE0000000 /*-2 << OpCode::StackChangeShift*/) };

static OpCode Br { InstructionCode::Br,
    ((u32)OperandType::InlineBrTarget) | ((u32)FlowControl::Branch << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | OpCode::EndsUncondJmpBlkFlag | (0 << OpCode::StackChangeShift) };

static OpCode Brfalse { InstructionCode::Brfalse,
    ((u32)OperandType::InlineBrTarget) | ((u32)FlowControl::Cond_Branch << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Brtrue { InstructionCode::Brtrue,
    ((u32)OperandType::InlineBrTarget) | ((u32)FlowControl::Cond_Branch << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Beq { InstructionCode::Beq,
    ((u32)OperandType::InlineBrTarget) | ((u32)FlowControl::Cond_Branch << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xE0000000 /*-2 << OpCode::StackChangeShift*/) };

static OpCode Bge { InstructionCode::Bge,
    ((u32)OperandType::InlineBrTarget) | ((u32)FlowControl::Cond_Branch << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xE0000000 /*-2 << OpCode::StackChangeShift*/) };

static OpCode Bgt { InstructionCode::Bgt,
    ((u32)OperandType::InlineBrTarget) | ((u32)FlowControl::Cond_Branch << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xE0000000 /*-2 << OpCode::StackChangeShift*/) };

static OpCode Ble { InstructionCode::Ble,
    ((u32)OperandType::InlineBrTarget) | ((u32)FlowControl::Cond_Branch << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xE0000000 /*-2 << OpCode::StackChangeShift*/) };

static OpCode Blt { InstructionCode::Blt,
    ((u32)OperandType::InlineBrTarget) | ((u32)FlowControl::Cond_Branch << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xE0000000 /*-2 << OpCode::StackChangeShift*/) };

static OpCode Bne_Un { InstructionCode::Bne_Un,
    ((u32)OperandType::InlineBrTarget) | ((u32)FlowControl::Cond_Branch << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xE0000000 /*-2 << OpCode::StackChangeShift*/) };

static OpCode Bge_Un { InstructionCode::Bge_Un,
    ((u32)OperandType::InlineBrTarget) | ((u32)FlowControl::Cond_Branch << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xE0000000 /*-2 << OpCode::StackChangeShift*/) };

static OpCode Bgt_Un { InstructionCode::Bgt_Un,
    ((u32)OperandType::InlineBrTarget) | ((u32)FlowControl::Cond_Branch << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xE0000000 /*-2 << OpCode::StackChangeShift*/) };

static OpCode Ble_Un { InstructionCode::Ble_Un,
    ((u32)OperandType::InlineBrTarget) | ((u32)FlowControl::Cond_Branch << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xE0000000 /*-2 << OpCode::StackChangeShift*/) };

static OpCode Blt_Un { InstructionCode::Blt_Un,
    ((u32)OperandType::InlineBrTarget) | ((u32)FlowControl::Cond_Branch << OpCode::FlowControlShift) | ((u32)OpCodeType::Macro << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xE0000000 /*-2 << OpCode::StackChangeShift*/) };

static OpCode Switch { InstructionCode::Switch,
    ((u32)OperandType::InlineSwitch) | ((u32)FlowControl::Cond_Branch << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Ldind_I1 { InstructionCode::Ldind_I1,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Ldind_U1 { InstructionCode::Ldind_U1,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Ldind_I2 { InstructionCode::Ldind_I2,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Ldind_U2 { InstructionCode::Ldind_U2,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Ldind_I4 { InstructionCode::Ldind_I4,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Ldind_U4 { InstructionCode::Ldind_U4,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Ldind_I8 { InstructionCode::Ldind_I8,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi8 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Ldind_I { InstructionCode::Ldind_I,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Ldind_R4 { InstructionCode::Ldind_R4,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushr4 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Ldind_R8 { InstructionCode::Ldind_R8,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushr8 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Ldind_Ref { InstructionCode::Ldind_Ref,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushref << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Stind_Ref { InstructionCode::Stind_Ref,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi_popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xE0000000 /*-2 << OpCode::StackChangeShift*/) };

static OpCode Stind_I1 { InstructionCode::Stind_I1,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi_popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xE0000000 /*-2 << OpCode::StackChangeShift*/) };

static OpCode Stind_I2 { InstructionCode::Stind_I2,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi_popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xE0000000 /*-2 << OpCode::StackChangeShift*/) };

static OpCode Stind_I4 { InstructionCode::Stind_I4,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi_popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xE0000000 /*-2 << OpCode::StackChangeShift*/) };

static OpCode Stind_I8 { InstructionCode::Stind_I8,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi_popi8 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xE0000000 /*-2 << OpCode::StackChangeShift*/) };

static OpCode Stind_R4 { InstructionCode::Stind_R4,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi_popr4 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xE0000000 /*-2 << OpCode::StackChangeShift*/) };

static OpCode Stind_R8 { InstructionCode::Stind_R8,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi_popr8 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xE0000000 /*-2 << OpCode::StackChangeShift*/) };

static OpCode Add { InstructionCode::Add,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Sub { InstructionCode::Sub,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Mul { InstructionCode::Mul,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Div { InstructionCode::Div,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Div_Un { InstructionCode::Div_Un,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Rem { InstructionCode::Rem,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Rem_Un { InstructionCode::Rem_Un,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode And { InstructionCode::And,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Or { InstructionCode::Or,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Xor { InstructionCode::Xor,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Shl { InstructionCode::Shl,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Shr { InstructionCode::Shr,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Shr_Un { InstructionCode::Shr_Un,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Neg { InstructionCode::Neg,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Not { InstructionCode::Not,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Conv_I1 { InstructionCode::Conv_I1,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Conv_I2 { InstructionCode::Conv_I2,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Conv_I4 { InstructionCode::Conv_I4,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Conv_I8 { InstructionCode::Conv_I8,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi8 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Conv_R4 { InstructionCode::Conv_R4,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushr4 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Conv_R8 { InstructionCode::Conv_R8,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushr8 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Conv_U4 { InstructionCode::Conv_U4,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Conv_U8 { InstructionCode::Conv_U8,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi8 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Callvirt { InstructionCode::Callvirt,
    ((u32)OperandType::InlineMethod) | ((u32)FlowControl::Call << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Varpop << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Varpush << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Cpobj { InstructionCode::Cpobj,
    ((u32)OperandType::InlineType) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi_popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xE0000000 /*-2 << OpCode::StackChangeShift*/) };

static OpCode Ldobj { InstructionCode::Ldobj,
    ((u32)OperandType::InlineType) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Ldstr { InstructionCode::Ldstr,
    ((u32)OperandType::InlineString) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushref << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Newobj { InstructionCode::Newobj,
    ((u32)OperandType::InlineMethod) | ((u32)FlowControl::Call << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Varpop << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushref << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Castclass { InstructionCode::Castclass,
    ((u32)OperandType::InlineType) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popref << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushref << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Isinst { InstructionCode::Isinst,
    ((u32)OperandType::InlineType) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popref << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Conv_R_Un { InstructionCode::Conv_R_Un,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushr8 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Unbox { InstructionCode::Unbox,
    ((u32)OperandType::InlineType) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popref << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Throw { InstructionCode::Throw,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Throw << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popref << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | OpCode::EndsUncondJmpBlkFlag | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Ldfld { InstructionCode::Ldfld,
    ((u32)OperandType::InlineField) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popref << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Ldflda { InstructionCode::Ldflda,
    ((u32)OperandType::InlineField) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popref << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Stfld { InstructionCode::Stfld,
    ((u32)OperandType::InlineField) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popref_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xE0000000 /*-2 << OpCode::StackChangeShift*/) };

static OpCode Ldsfld { InstructionCode::Ldsfld,
    ((u32)OperandType::InlineField) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Ldsflda { InstructionCode::Ldsflda,
    ((u32)OperandType::InlineField) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Stsfld { InstructionCode::Stsfld,
    ((u32)OperandType::InlineField) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Stobj { InstructionCode::Stobj,
    ((u32)OperandType::InlineType) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xE0000000 /*-2 << OpCode::StackChangeShift*/) };

static OpCode Conv_Ovf_I1_Un { InstructionCode::Conv_Ovf_I1_Un,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Conv_Ovf_I2_Un { InstructionCode::Conv_Ovf_I2_Un,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Conv_Ovf_I4_Un { InstructionCode::Conv_Ovf_I4_Un,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Conv_Ovf_I8_Un { InstructionCode::Conv_Ovf_I8_Un,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi8 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Conv_Ovf_U1_Un { InstructionCode::Conv_Ovf_U1_Un,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Conv_Ovf_U2_Un { InstructionCode::Conv_Ovf_U2_Un,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Conv_Ovf_U4_Un { InstructionCode::Conv_Ovf_U4_Un,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Conv_Ovf_U8_Un { InstructionCode::Conv_Ovf_U8_Un,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi8 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Conv_Ovf_I_Un { InstructionCode::Conv_Ovf_I_Un,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Conv_Ovf_U_Un { InstructionCode::Conv_Ovf_U_Un,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Box { InstructionCode::Box,
    ((u32)OperandType::InlineType) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushref << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Newarr { InstructionCode::Newarr,
    ((u32)OperandType::InlineType) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushref << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Ldlen { InstructionCode::Ldlen,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popref << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Ldelema { InstructionCode::Ldelema,
    ((u32)OperandType::InlineType) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popref_popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Ldelem_I1 { InstructionCode::Ldelem_I1,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popref_popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Ldelem_U1 { InstructionCode::Ldelem_U1,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popref_popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Ldelem_I2 { InstructionCode::Ldelem_I2,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popref_popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Ldelem_U2 { InstructionCode::Ldelem_U2,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popref_popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Ldelem_I4 { InstructionCode::Ldelem_I4,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popref_popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Ldelem_U4 { InstructionCode::Ldelem_U4,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popref_popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Ldelem_I8 { InstructionCode::Ldelem_I8,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popref_popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi8 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Ldelem_I { InstructionCode::Ldelem_I,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popref_popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Ldelem_R4 { InstructionCode::Ldelem_R4,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popref_popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushr4 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Ldelem_R8 { InstructionCode::Ldelem_R8,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popref_popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushr8 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Ldelem_Ref { InstructionCode::Ldelem_Ref,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popref_popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushref << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Stelem_I { InstructionCode::Stelem_I,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popref_popi_popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xD0000000 /*-3 << OpCode::StackChangeShift*/) };

static OpCode Stelem_I1 { InstructionCode::Stelem_I1,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popref_popi_popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xD0000000 /*-3 << OpCode::StackChangeShift*/) };

static OpCode Stelem_I2 { InstructionCode::Stelem_I2,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popref_popi_popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xD0000000 /*-3 << OpCode::StackChangeShift*/) };

static OpCode Stelem_I4 { InstructionCode::Stelem_I4,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popref_popi_popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xD0000000 /*-3 << OpCode::StackChangeShift*/) };

static OpCode Stelem_I8 { InstructionCode::Stelem_I8,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popref_popi_popi8 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xD0000000 /*-3 << OpCode::StackChangeShift*/) };

static OpCode Stelem_R4 { InstructionCode::Stelem_R4,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popref_popi_popr4 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xD0000000 /*-3 << OpCode::StackChangeShift*/) };

static OpCode Stelem_R8 { InstructionCode::Stelem_R8,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popref_popi_popr8 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xD0000000 /*-3 << OpCode::StackChangeShift*/) };

static OpCode Stelem_Ref { InstructionCode::Stelem_Ref,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popref_popi_popref << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xD0000000 /*-3 << OpCode::StackChangeShift*/) };

static OpCode Ldelem { InstructionCode::Ldelem,
    ((u32)OperandType::InlineType) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popref_popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Stelem { InstructionCode::Stelem,
    ((u32)OperandType::InlineType) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popref_popi_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Unbox_Any { InstructionCode::Unbox_Any,
    ((u32)OperandType::InlineType) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popref << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Conv_Ovf_I1 { InstructionCode::Conv_Ovf_I1,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Conv_Ovf_U1 { InstructionCode::Conv_Ovf_U1,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Conv_Ovf_I2 { InstructionCode::Conv_Ovf_I2,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Conv_Ovf_U2 { InstructionCode::Conv_Ovf_U2,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Conv_Ovf_I4 { InstructionCode::Conv_Ovf_I4,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Conv_Ovf_U4 { InstructionCode::Conv_Ovf_U4,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Conv_Ovf_I8 { InstructionCode::Conv_Ovf_I8,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi8 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Conv_Ovf_U8 { InstructionCode::Conv_Ovf_U8,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi8 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Refanyval { InstructionCode::Refanyval,
    ((u32)OperandType::InlineType) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Ckfinite { InstructionCode::Ckfinite,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushr8 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Mkrefany { InstructionCode::Mkrefany,
    ((u32)OperandType::InlineType) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Ldtoken { InstructionCode::Ldtoken,
    ((u32)OperandType::InlineTok) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Conv_U2 { InstructionCode::Conv_U2,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Conv_U1 { InstructionCode::Conv_U1,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Conv_I { InstructionCode::Conv_I,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Conv_Ovf_I { InstructionCode::Conv_Ovf_I,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Conv_Ovf_U { InstructionCode::Conv_Ovf_U,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Add_Ovf { InstructionCode::Add_Ovf,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Add_Ovf_Un { InstructionCode::Add_Ovf_Un,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Mul_Ovf { InstructionCode::Mul_Ovf,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Mul_Ovf_Un { InstructionCode::Mul_Ovf_Un,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Sub_Ovf { InstructionCode::Sub_Ovf,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Sub_Ovf_Un { InstructionCode::Sub_Ovf_Un,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Endfinally { InstructionCode::Endfinally,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Return << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | OpCode::EndsUncondJmpBlkFlag | (0 << OpCode::StackChangeShift) };

static OpCode Leave { InstructionCode::Leave,
    ((u32)OperandType::InlineBrTarget) | ((u32)FlowControl::Branch << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | OpCode::EndsUncondJmpBlkFlag | (0 << OpCode::StackChangeShift) };

static OpCode Leave_S { InstructionCode::Leave_S,
    ((u32)OperandType::ShortInlineBrTarget) | ((u32)FlowControl::Branch << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | OpCode::EndsUncondJmpBlkFlag | (0 << OpCode::StackChangeShift) };

static OpCode Stind_I { InstructionCode::Stind_I,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi_popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0xE0000000 /*-2 << OpCode::StackChangeShift*/) };

static OpCode Conv_U { InstructionCode::Conv_U,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Prefix7 { InstructionCode::Prefix7,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Meta << OpCode::FlowControlShift) | ((u32)OpCodeType::Nternal << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Prefix6 { InstructionCode::Prefix6,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Meta << OpCode::FlowControlShift) | ((u32)OpCodeType::Nternal << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Prefix5 { InstructionCode::Prefix5,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Meta << OpCode::FlowControlShift) | ((u32)OpCodeType::Nternal << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Prefix4 { InstructionCode::Prefix4,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Meta << OpCode::FlowControlShift) | ((u32)OpCodeType::Nternal << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Prefix3 { InstructionCode::Prefix3,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Meta << OpCode::FlowControlShift) | ((u32)OpCodeType::Nternal << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Prefix2 { InstructionCode::Prefix2,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Meta << OpCode::FlowControlShift) | ((u32)OpCodeType::Nternal << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Prefix1 { InstructionCode::Prefix1,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Meta << OpCode::FlowControlShift) | ((u32)OpCodeType::Nternal << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Prefixref { InstructionCode::Prefixref,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Meta << OpCode::FlowControlShift) | ((u32)OpCodeType::Nternal << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (1 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Arglist { InstructionCode::Arglist,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (2 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Ceq { InstructionCode::Ceq,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (2 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Cgt { InstructionCode::Cgt,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (2 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Cgt_Un { InstructionCode::Cgt_Un,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (2 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Clt { InstructionCode::Clt,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (2 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Clt_Un { InstructionCode::Clt_Un,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1_pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (2 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Ldftn { InstructionCode::Ldftn,
    ((u32)OperandType::InlineMethod) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (2 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Ldvirtftn { InstructionCode::Ldvirtftn,
    ((u32)OperandType::InlineMethod) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popref << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (2 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Ldarg { InstructionCode::Ldarg,
    ((u32)OperandType::InlineVar) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (2 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Ldarga { InstructionCode::Ldarga,
    ((u32)OperandType::InlineVar) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (2 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Starg { InstructionCode::Starg,
    ((u32)OperandType::InlineVar) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (2 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Ldloc { InstructionCode::Ldloc,
    ((u32)OperandType::InlineVar) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push1 << OpCode::StackBehaviorPushShift) | (2 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Ldloca { InstructionCode::Ldloca,
    ((u32)OperandType::InlineVar) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (2 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Stloc { InstructionCode::Stloc,
    ((u32)OperandType::InlineVar) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (2 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Localloc { InstructionCode::Localloc,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (2 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Endfilter { InstructionCode::Endfilter,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Return << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (2 << OpCode::SizeShift) | OpCode::EndsUncondJmpBlkFlag | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Unaligned { InstructionCode::Unaligned,
    ((u32)OperandType::ShortInlineI) | ((u32)FlowControl::Meta << OpCode::FlowControlShift) | ((u32)OpCodeType::Prefix << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (2 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Volatile { InstructionCode::Volatile,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Meta << OpCode::FlowControlShift) | ((u32)OpCodeType::Prefix << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (2 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Tailcall { InstructionCode::Tailcall,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Meta << OpCode::FlowControlShift) | ((u32)OpCodeType::Prefix << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (2 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Initobj { InstructionCode::Initobj,
    ((u32)OperandType::InlineType) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (2 << OpCode::SizeShift) | (0xF0000000 /*-1 << OpCode::StackChangeShift*/) };

static OpCode Constrained { InstructionCode::Constrained,
    ((u32)OperandType::InlineType) | ((u32)FlowControl::Meta << OpCode::FlowControlShift) | ((u32)OpCodeType::Prefix << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (2 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Cpblk { InstructionCode::Cpblk,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi_popi_popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (2 << OpCode::SizeShift) | (0xD0000000 /*-3 << OpCode::StackChangeShift*/) };

static OpCode Initblk { InstructionCode::Initblk,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Popi_popi_popi << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (2 << OpCode::SizeShift) | (0xD0000000 /*-3 << OpCode::StackChangeShift*/) };

static OpCode Rethrow { InstructionCode::Rethrow,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Throw << OpCode::FlowControlShift) | ((u32)OpCodeType::Objmodel << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (2 << OpCode::SizeShift) | OpCode::EndsUncondJmpBlkFlag | (0 << OpCode::StackChangeShift) };

static OpCode Sizeof { InstructionCode::Sizeof,
    ((u32)OperandType::InlineType) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (2 << OpCode::SizeShift) | (1 << OpCode::StackChangeShift) };

static OpCode Refanytype { InstructionCode::Refanytype,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Next << OpCode::FlowControlShift) | ((u32)OpCodeType::Primitive << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop1 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Pushi << OpCode::StackBehaviorPushShift) | (2 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

static OpCode Readonly { InstructionCode::Readonly,
    ((u32)OperandType::InlineNone) | ((u32)FlowControl::Meta << OpCode::FlowControlShift) | ((u32)OpCodeType::Prefix << OpCode::OpCodeTypeShift) | ((u32)StackBehavior::Pop0 << OpCode::StackBehaviorPopShift) | ((u32)StackBehavior::Push0 << OpCode::StackBehaviorPushShift) | (2 << OpCode::SizeShift) | (0 << OpCode::StackChangeShift) };

}

static HashMap<i16, OpCode> opcodes {
#define __ENUMERATE_INSTRUCTION_CODE(name, id) { id, OpCodes::name },
    ENUMERATE_INSTRUCTION_CODES
};
}
