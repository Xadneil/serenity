/*
 * Copyright (c) 2021, Daniel Flaws <dflaws1@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#pragma once

#include "Enums.h"
#include "IO.h"
#include <AK/ByteReader.h>
#include <AK/Result.h>
#include <AK/Span.h>
#include <AK/Vector.h>

namespace DotNETRuntime {
struct Section {
    String name;
    size_t virtual_size { 0 };
    unsigned virtual_address { 0 };
    size_t size_of_raw_data { 0 };
    unsigned pointer_to_raw_data { 0 };
    unsigned pointer_to_relocations { 0 };
    unsigned pointer_to_line_numbers { 0 };
    unsigned short number_of_relocations { 0 };
    unsigned short number_of_line_numbers { 0 };
    unsigned characteristics { 0 };
};

struct DataDirectory {
    unsigned virtual_address { 0 };
    size_t size { 0 };
};

#define JUMP_IMMEDIATE_32                            \
    {                                                \
        auto v32 = IO::read_u32(reader);             \
        if (!v32.has_value()) {                      \
            warnln("Could not read jump immediate"); \
            VERIFY_NOT_REACHED();                    \
        }                                            \
        if (v32.value() >= fileContents.size()) {    \
            warnln("Jump immediate was too large");  \
            VERIFY_NOT_REACHED();                    \
        }                                            \
        reader.seek(v32.value());                    \
    }
#define READ_DATA_DIRECTORY(name)                                  \
    DataDirectory name;                                            \
    {                                                              \
        auto tmp_##name = PEImage::read_data_directory(reader);    \
        if (!tmp_##name.has_value()) {                             \
            warnln("Could not read data directory \"" #name "\""); \
            VERIFY_NOT_REACHED();                                  \
        }                                                          \
        name = tmp_##name.value();                                 \
    }
#define READ_ZERO_TERMINATED_STRING(name, length)                          \
    String name;                                                           \
    {                                                                      \
        auto tmp_##name = IO::read_zero_terminated_string(reader, length); \
        if (!tmp_##name.has_value()) {                                     \
            warnln("Could not read \"" #name "\"");                        \
            VERIFY_NOT_REACHED();                                          \
        }                                                                  \
        name = tmp_##name.value();                                         \
    }
#define READ_ALIGNED_STRING(name, length)                          \
    String name;                                                   \
    {                                                              \
        auto tmp_##name = IO::read_aligned_string(reader, length); \
        if (!tmp_##name.has_value()) {                             \
            warnln("Could not read \"" #name "\"");                \
            VERIFY_NOT_REACHED();                                  \
        }                                                          \
        name = tmp_##name.value();                                 \
    }
#define ALIGN4                                 \
    {                                          \
        auto position = reader.offset();       \
        reader.seek(((position + 3) / 4) * 4); \
    }

struct PEImage {
    TargetArchitecture architecture;
    ModuleKind module_kind;
    ModuleCharacteristics characteristics;
    ModuleAttributes attributes;
    unsigned entry_point_token { 0 };
    Vector<Section> sections;
    DataDirectory metadata;
    DataDirectory debug;
    DataDirectory resources;
    DataDirectory strong_name;

    static Optional<DataDirectory> read_data_directory(InputMemoryStream& reader)
    {
        auto v32 = IO::read_u32(reader);
        if (!v32.has_value())
            return {};
        auto virtual_address = v32.value();
        v32 = IO::read_u32(reader);
        if (!v32.has_value())
            return {};
        auto size = v32.value();
        return DataDirectory { virtual_address, size };
    }

    static u32 resolve_virtual_address(Vector<Section> const& sections, u32 virtual_address)
    {
        for (auto section : sections) {
            if (virtual_address >= section.virtual_address && virtual_address < section.virtual_address + section.size_of_raw_data)
                return section.pointer_to_raw_data + virtual_address - section.virtual_address;
        }
        VERIFY_NOT_REACHED();
    }

    static ErrorOr<PEImage> read_portable_executable(const ByteBuffer fileContents)
    {
        InputMemoryStream reader(fileContents);
        READ_16(pe_header)
        if (pe_header != 0x5a4d)
            return Error::from_string_literal("Bad PE Header");
        SKIP(58)
        JUMP_IMMEDIATE_32
        READ_32(nt_header)
        if (nt_header != 0x4550)
            return Error::from_string_literal("Bad NT Header");
        READ_16(architecture)
        READ_16(number_of_sections)
        SKIP(14)
        READ_16(characteristics)
        READ_16(bitness)
        bool _64_bit = bitness == 0x20b;
        SKIP(66)
        READ_16(subsystem)
        READ_16(dll_characteristics)
        SKIP(_64_bit ? 88 : 72)
        READ_DATA_DIRECTORY(debug)
        SKIP(56)
        READ_DATA_DIRECTORY(cli_header)
        if (cli_header.size == 0 && cli_header.virtual_address == 0)
            return Error::from_string_literal("Not a CLI Image");
        SKIP(8)

        ModuleKind module_kind;
        if ((characteristics & 0x2000) != 0)
            module_kind = ModuleKind::Dll;
        else if (subsystem == 2 || subsystem == 9)
            module_kind = ModuleKind::Windows;
        else
            module_kind = ModuleKind::Console;

        Vector<Section> sections;
        for (size_t i = 0; i < number_of_sections; i++) {
            READ_ZERO_TERMINATED_STRING(name, 8)
            READ_32(virtual_size)
            READ_32(virtual_address)
            READ_32(size_of_raw_data)
            READ_32(pointer_to_raw_data)
            READ_32(pointer_to_relocations)
            READ_32(pointer_to_line_numbers)
            READ_16(number_of_relocations)
            READ_16(number_of_line_numbers)
            READ_32(characteristics)

            sections.append(Section {
                .name = name,
                .virtual_size = virtual_size,
                .virtual_address = virtual_address,
                .size_of_raw_data = size_of_raw_data,
                .pointer_to_raw_data = pointer_to_raw_data,
                .pointer_to_relocations = pointer_to_relocations,
                .pointer_to_line_numbers = pointer_to_line_numbers,
                .number_of_relocations = number_of_relocations,
                .number_of_line_numbers = number_of_line_numbers,
                .characteristics = characteristics,
            });
        }

        reader.seek(resolve_virtual_address(sections, cli_header.virtual_address));
        SKIP(8);
        READ_DATA_DIRECTORY(metadata)
        READ_32(attributes)
        READ_32(entry_point)
        READ_DATA_DIRECTORY(resources)
        READ_DATA_DIRECTORY(strong_name)

        PEImage image {
            .architecture = (TargetArchitecture)architecture,
            .module_kind = (ModuleKind)module_kind,
            .characteristics = (ModuleCharacteristics)dll_characteristics,
            .attributes = (ModuleAttributes)attributes,
            .entry_point_token = entry_point,
            .sections = sections,
            .metadata = metadata,
            .debug = debug,
            .resources = resources,
            .strong_name = strong_name,
        };
        return { image };
    }
};

}
