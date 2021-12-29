/*
 * Copyright (c) 2021, Daniel Flaws <dflaws1@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#pragma once

#include <AK/MemoryStream.h>
#include <AK/Optional.h>
#include <AK/String.h>
#include <AK/StringView.h>
#include <AK/Types.h>

namespace DotNETRuntime {
#define READ_8(name)                                \
    u8 name;                                        \
    {                                               \
        u8 buffer[1];                               \
        if (!reader.read_or_error({ buffer, 1 })) { \
            warnln("Could not read \"" #name "\""); \
            VERIFY_NOT_REACHED();                   \
        }                                           \
        name = buffer[0];                           \
    }
#define READ_16(name)                               \
    u16 name;                                       \
    {                                               \
        auto v16 = IO::read_u16(reader);            \
        if (!v16.has_value()) {                     \
            warnln("Could not read \"" #name "\""); \
            VERIFY_NOT_REACHED();                   \
        }                                           \
        name = v16.value();                         \
    }
#define READ_32(name)                               \
    u32 name;                                       \
    {                                               \
        auto v32 = IO::read_u32(reader);            \
        if (!v32.has_value()) {                     \
            warnln("Could not read \"" #name "\""); \
            VERIFY_NOT_REACHED();                   \
        }                                           \
        name = v32.value();                         \
    }
#define READ_64(name)                               \
    u64 name;                                       \
    {                                               \
        auto v64 = IO::read_u64(reader);            \
        if (!v64.has_value()) {                     \
            warnln("Could not read \"" #name "\""); \
            VERIFY_NOT_REACHED();                   \
        }                                           \
        name = v64.value();                         \
    }
#define SKIP(count)                         \
    if (!reader.discard_or_error(count)) {  \
        warnln("Could not skip {}", count); \
        VERIFY_NOT_REACHED();               \
    }

struct IO {
    static float read_float_verify(InputMemoryStream& reader)
    {
        static u8 buffer[4];
        bool success = reader.read_or_error({ buffer, 4 });
        VERIFY(success);
        //u32 tmpBuffer = (u32)(buffer[0] | buffer[1] << 8 | buffer[2] << 16 | buffer[3] << 24);
        return *((float*)buffer);
    }

    static double read_double_verify(InputMemoryStream& reader)
    {
        static u8 buffer[8];
        bool success = reader.read_or_error({ buffer, 8 });
        VERIFY(success);
        // u32 lo = (u32)(buffer[0] | buffer[1] << 8 |
        //     buffer[2] << 16 | buffer[3] << 24);
        // u32 hi = (u32)(buffer[4] | buffer[5] << 8 |
        //     buffer[6] << 16 | buffer[7] << 24);

        // u64 tmpBuffer = ((u64)hi) << 32 | lo;
        return *((double*)buffer);
    }

    static Optional<u64> read_u64(InputMemoryStream& reader)
    {
        static u8 buffer[8];
        if (!reader.read_or_error({ buffer, 8 }))
            return {};
        return (((u64)buffer[7]) << 56 | ((u64)buffer[6]) << 48 | ((u64)buffer[5]) << 40 | ((u64)buffer[4]) << 32 | ((u64)buffer[3]) << 24 | ((u64)buffer[2]) << 16 | ((u64)buffer[1]) << 8 | ((u64)buffer[0]));
    }

    static u64 read_u64_verify(InputMemoryStream& reader)
    {
        static u8 buffer[8];
        bool success = reader.read_or_error({ buffer, 8 });
        VERIFY(success);
        return (((u64)buffer[7]) << 56 | ((u64)buffer[6]) << 48 | ((u64)buffer[5]) << 40 | ((u64)buffer[4]) << 32 | ((u64)buffer[3]) << 24 | ((u64)buffer[2]) << 16 | ((u64)buffer[1]) << 8 | ((u64)buffer[0]));
    }

    static Optional<u32> read_u32(InputMemoryStream& reader)
    {
        static u8 buffer[4];
        if (!reader.read_or_error({ buffer, 4 }))
            return {};
        return (((u32)buffer[3]) << 24 | ((u32)buffer[2]) << 16 | ((u32)buffer[1]) << 8 | ((u32)buffer[0]));
    }

    static u32 read_u32_verify(InputMemoryStream& reader)
    {
        static u8 buffer[4];
        bool success = reader.read_or_error({ buffer, 4 });
        VERIFY(success);
        return (((u32)buffer[3]) << 24 | ((u32)buffer[2]) << 16 | ((u32)buffer[1]) << 8 | ((u32)buffer[0]));
    }

    static Optional<u16> read_u16(InputMemoryStream& reader)
    {
        static u8 buffer[2];
        if (!reader.read_or_error({ buffer, 2 })) {
            return {};
        }
        return (((u16)buffer[1]) << 8 | ((u16)buffer[0]));
    }

    static u8 read_u8_verify(InputMemoryStream& reader)
    {
        static u8 buffer[1];
        bool success = reader.read_or_error({ buffer, 1 });
        VERIFY(success);
        return buffer[0];
    }

    static Optional<String> read_zero_terminated_string(InputMemoryStream& reader, size_t length)
    {
        u8 buffer[length];
        if (!reader.read_or_error({ buffer, length }))
            return {};
        for (size_t i = 0; i < length; i++) {
            if (buffer[0] == 0)
                return String(StringView { buffer, i });
        }
        return StringView { buffer, length };
    }

    static Optional<String> read_aligned_string(InputMemoryStream& reader, size_t max_length)
    {
        size_t bytes_read = 0;
        bool reading = true;
        StringBuilder builder;
        u8 buffer[1];
        while (reading && (bytes_read < max_length)) {
            if (!reader.read_or_error({ buffer, 1 }))
                return {};
            reading = buffer[0] != 0;
            bytes_read += reading ? 1 : 0;
            if (reading)
                builder.append(buffer[0]);
        }
        auto align = -1 + ((bytes_read + 4) & ~3) - bytes_read;
        if (!reader.discard_or_error(align)) {
            printf("read_aligned_string: failed to align");
            return {};
        }
        return builder.to_string();
    }

    static Optional<String> read_utf8(InputMemoryStream& reader)
    {
        bool reading = true;
        StringBuilder builder;
        u8 buffer[1];
        while (reading) {
            if (!reader.read_or_error({ buffer, 1 }))
                return {};
            reading = buffer[0] != 0;
            if (reading)
                builder.append(buffer[0]);
        }
        return builder.to_string();
    }

    // static Optional<String> read_utf8(InputMemoryStream& reader, size_t length)
    // {
    //     u8 buffer[length];
    //     if (!reader.read_or_error({ buffer, length }))
    //         return {};
    //     return String { StringView { buffer, length } };
    // }

    static u32 read_packed_int(InputMemoryStream& reader)
    {
        u8 buffer[2];
        bool success;
        success = reader.read_or_error({ buffer, 1 });
        VERIFY(success);
        u8 b0 = buffer[0];
        if ((b0 & 0x80) == 0)
            return b0;
        success = reader.read_or_error({ buffer, 1 });
        VERIFY(success);
        u8 b1 = buffer[0];
        if ((b0 & 0xC0) == 0x80)
            return ((b0 & 0x3F) << 8) | b1;
        success = reader.read_or_error({ buffer, 2 });
        VERIFY(success);
        u8 b2 = buffer[0];
        u8 b3 = buffer[1];
        return ((b0 & 0x3F) << 24) | (b1 << 16) | (b2 << 8) | b3;
    }
};
}
