/*
 * Copyright (c) 2021, Daniel Flaws <dflaws1@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#pragma once

#include "Enums.h"
#include "IO.h"
#include "OpCodes.h"
#include <AK/BinarySearch.h>
#include <AK/MemoryStream.h>
#include <AK/Variant.h>
#include <AK/Vector.h>

namespace DotNETRuntime {
using SwitchTarget = Vector<i32>;

struct InstructionOperand {
    enum class Type {
        NoOperand,
        Int32Operand,
        Int64Operand,
        Float32Operand,
        Float64Operand,
        SwitchTarget,
        BranchTarget,
        MetadataToken,
    };
    Type type() const { return m_type; }
    i32 int_32_operand() const
    {
        VERIFY(m_type == Type::Int32Operand);
        return m_value.get<i32>();
    }
    i64 int_64_operand() const
    {
        VERIFY(m_type == Type::Int64Operand);
        return m_value.get<i64>();
    }
    float float_32_operand() const
    {
        VERIFY(m_type == Type::Float32Operand);
        return m_value.get<float>();
    }
    double float_64_operand() const
    {
        VERIFY(m_type == Type::Float64Operand);
        return m_value.get<double>();
    }
    SwitchTarget& switch_target()
    {
        VERIFY(m_type == Type::SwitchTarget);
        return m_value.get<SwitchTarget>();
    }
    i32 branch_target() const
    {
        VERIFY(m_type == Type::BranchTarget);
        return m_value.get<i32>();
    }
    i32 metadata_token() const
    {
        VERIFY(m_type == Type::MetadataToken);
        return m_value.get<i32>();
    }
    explicit InstructionOperand()
        : m_value(0)
        , m_type(InstructionOperand::Type::NoOperand)
    {
    }
    InstructionOperand(Type type, i32 value)
        : m_value(value)
        , m_type(type)
    {
    }
    explicit InstructionOperand(i64 value)
        : m_value(value)
        , m_type(Type::Int64Operand)
    {
    }
    explicit InstructionOperand(float value)
        : m_value(value)
        , m_type(Type::Float32Operand)
    {
    }
    explicit InstructionOperand(double value)
        : m_value(value)
        , m_type(Type::Float64Operand)
    {
    }
    explicit InstructionOperand(SwitchTarget value)
        : m_value(value)
        , m_type(Type::SwitchTarget)
    {
    }

private:
    using Value = AK::Variant<i32, i64, float, double, SwitchTarget>;

    Value m_value;
    Type m_type;
};

struct Instruction {
    size_t offset { 0 };
    OpCode op_code;
    InstructionCode instruction_code;
    InstructionOperand instruction_operand;

    bool is_branch() const
    {
        return instruction_code == InstructionCode::Switch || op_code.flow_control() == FlowControl::Branch || op_code.flow_control() == FlowControl::Cond_Branch;
    }
};

enum class MethodBodyFlags {
    None = 0,
    SmallFormat = 0x00,
    TinyFormat = 0x02,
    FatFormat = 0x03,
    TinyFormat1 = 0x06,
    FormatMask = 0x07,
    InitLocals = 0x10,
    MoreSects = 0x08
};

enum class SEHFlags {
    Catch = 0x00,
    Filter = 0x01,
    Finally = 0x02,
    Fault = 0x04,
    TypeMask = 0x07,
};

struct SEHBlock {
    SEHFlags flags;
    u32 try_offset { 0 };
    size_t try_length { 0 };
    u32 handler_offset { 0 };
    size_t handler_length { 0 };
    size_t value { 0 };
};

struct MethodBody {
    size_t max_stack_size { 0 };
    u32 local_sig { 0 };
    Vector<Instruction> code;
    Vector<SEHBlock> seh_blocks;

    static MethodBody read_method_body(InputMemoryStream& reader)
    {
        u8 lsb;
        bool success = reader.read_or_error({ &lsb, 1 });
        VERIFY(success);
        int flags = lsb;
        auto format = (MethodBodyFlags)(flags & (int)MethodBodyFlags::FormatMask);

        switch (format) {
        case MethodBodyFlags::FatFormat: {
            u8 msb;
            success = reader.read_or_error({ &msb, 1 });
            VERIFY(success);
            unsigned dword_multiple_size = (msb & 0xF0) >> 4;
            VERIFY(dword_multiple_size == 3);
            u16 max_stack_size;
            success = reader.read_or_error({ &max_stack_size, 2 });
            VERIFY(success);
            int code_size;
            success = reader.read_or_error({ &code_size, 4 });
            VERIFY(success);
            unsigned local_signature;
            success = reader.read_or_error({ &local_signature, 4 });
            VERIFY(success);
            auto flags2 = (msb & 0x0F) << 8 | lsb;
            auto code = read_instructions(reader, code_size);
            Vector<SEHBlock> seh_blocks;
            if ((flags2 & (int)MethodBodyFlags::MoreSects) != 0) {
                //read_seh_blocks
                TODO();
            }
            return MethodBody {
                .max_stack_size = max_stack_size,
                .local_sig = local_signature,
                .code = code,
                .seh_blocks = seh_blocks
            };
        }
        case MethodBodyFlags::TinyFormat:
        case MethodBodyFlags::TinyFormat1: {
            auto code_size = (flags & 0b11111100) >> 2;
            auto code = read_instructions(reader, code_size);
            return MethodBody {
                .max_stack_size = 8,
                .local_sig = 0,
                .code = code,
                .seh_blocks = {}
            };
        }
        default:
            VERIFY_NOT_REACHED();
        }
    }

    static OpCode read_opcode(InputMemoryStream& reader)
    {
        u8 b1;
        bool success = reader.read_or_error({ &b1, 1 });
        VERIFY(success);
        if (b1 == 0xfe) {
            u8 b2;
            success = reader.read_or_error({ &b2, 1 });
            VERIFY(success);
            i16 opcode = ((i16)b2 << 8) & b2;
            return *opcodes.get(opcode);
        } else {
            return *opcodes.get(b1);
        }
    }

    static InstructionOperand read_operand(InputMemoryStream& reader, OpCode const& opcode, i64 start_position)
    {
        switch (opcode.operand_type()) {
        case OperandType::InlineI:
            return InstructionOperand { InstructionOperand::Type::Int32Operand, (int)IO::read_u32_verify(reader) };
        case OperandType::ShortInlineI:
            return InstructionOperand { InstructionOperand::Type::Int32Operand, (int)IO::read_u8_verify(reader) };
        case OperandType::InlineI8:
            return InstructionOperand { (i64)IO::read_u64_verify(reader) };
        case OperandType::InlineR:
            return InstructionOperand { IO::read_double_verify(reader) };
        case OperandType::ShortInlineR:
            return InstructionOperand { IO::read_float_verify(reader) };
        case OperandType::InlineString:
            return InstructionOperand { InstructionOperand::Type::MetadataToken, (int)IO::read_u32_verify(reader) };
        case OperandType::InlineBrTarget: {
            i64 offset = (i32)IO::read_u32_verify(reader);
            return InstructionOperand { InstructionOperand::Type::BranchTarget, (i32)(offset + reader.offset() - start_position) };
        }
        case OperandType::ShortInlineBrTarget: {
            i64 offset = (i8)IO::read_u8_verify(reader);
            return InstructionOperand { InstructionOperand::Type::BranchTarget, (i32)(offset + reader.offset() - start_position) };
        }
        case OperandType::InlineSwitch: {
            auto branch_count = IO::read_u32_verify(reader);
            SwitchTarget branches;
            for (size_t i = 0; i < branch_count; i++) {
                branches.append(IO::read_u32_verify(reader));
            }
            auto shift = reader.offset() - start_position;
            for (size_t i = 0; i < branch_count; i++) {
                branches[i] += shift;
            }
            return InstructionOperand { branches };
        }
        case OperandType::InlineVar:
            return InstructionOperand { InstructionOperand::Type::Int32Operand, (int)IO::read_u32_verify(reader) };
        case OperandType::ShortInlineVar:
            return InstructionOperand { InstructionOperand::Type::Int32Operand, (int)IO::read_u8_verify(reader) };
        case OperandType::InlineField:
        case OperandType::InlineMethod:
        case OperandType::InlineSig:
        case OperandType::InlineTok:
        case OperandType::InlineType:
            return InstructionOperand { InstructionOperand::Type::MetadataToken, (int)IO::read_u32_verify(reader) };
        case OperandType::InlineNone:
            return InstructionOperand {};
        default:
            VERIFY_NOT_REACHED();
        }
    }

    static Instruction read_instruction(InputMemoryStream& reader, int start_position)
    {
        auto offset = reader.offset() - start_position;
        auto opcode = read_opcode(reader);
        Instruction instruction {
            .offset = offset,
            .op_code = opcode,
            .instruction_code = (InstructionCode)opcode.value(),
            .instruction_operand = read_operand(reader, opcode, start_position)
        };
        return instruction;
    }

    static Vector<Instruction> read_instructions(InputMemoryStream& reader, int code_size)
    {
        auto start_offset = reader.offset();
        bool has_branches = false;
        Vector<Instruction> result;
        int offset = 0;
        while (offset < code_size) {
            auto position = reader.offset();
            auto i = read_instruction(reader, start_offset);
            has_branches = has_branches || i.is_branch();
            offset = offset + (reader.offset() - position);
            result.append(i);
        }
        if (!has_branches)
            return result;
        Vector<size_t> offsets;
        offsets.ensure_capacity(result.size());
        for (auto& instruction : result) {
            offsets.append(instruction.offset);
        }
        auto idx = [&](size_t offset) {
            size_t nearby_index;
            binary_search(offsets, offset, &nearby_index);
            return nearby_index;
        };
        for (auto& instruction : result) {
            if (instruction.is_branch()) {
                if (instruction.instruction_operand.type() == InstructionOperand::Type::SwitchTarget) {
                    auto size = instruction.instruction_operand.switch_target().size();
                    for (size_t i = 0; i < size; i++) {
                        instruction.instruction_operand.switch_target()[i] = idx(instruction.instruction_operand.switch_target()[i]);
                    }
                } else if (instruction.instruction_operand.type() == InstructionOperand::Type::BranchTarget) {
                    instruction.instruction_operand = InstructionOperand { InstructionOperand::Type::BranchTarget, (int)idx(instruction.instruction_operand.branch_target()) };
                } else {
                    VERIFY_NOT_REACHED();
                }
            }
        }
        return result;
    }
};

}
