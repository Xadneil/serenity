/*
 * Copyright (c) 2021, Daniel Flaws <dflaws1@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#pragma once

#include "CodedIndex.h"
#include "Enums.h"
#include "Forward.h"
#include "Guid.h"
#include "IO.h"
#include "MethodBody.h"
#include "PortableExecutableImage.h"
#include "Schema.h"
#include "Types.h"
#include <AK/Function.h>
#include <AK/HashMap.h>
#include <AK/MemoryStream.h>
#include <AK/String.h>
#include <LibCore/File.h>

namespace DotNETRuntime {
struct HeapHeader {
    size_t offset { 0 };
    size_t size { 0 };
    String name;
};

class MetadataReader : public RefCounted<MetadataReader> {
public:
    static ErrorOr<NonnullRefPtr<MetadataReader>> create_from_file(String file_name)
    {
        auto file = TRY(Core::File::open(file_name, Core::OpenMode::ReadOnly));
        auto contents = file->read_all();
        auto image = TRY(PEImage::read_portable_executable(contents));
        return adopt_ref(*new MetadataReader(move(contents), image));
    }

    int row_count(TableId const i) const
    {
        return m_row_counts[(size_t)i].value_or(0);
    }

    String const read_string(size_t i)
    {
        VERIFY(i < m_string_stream.size);
        reader.seek(m_string_stream.offset + i);
        auto result = IO::read_utf8(reader);
        VERIFY(result.has_value());
        return String { result.value() };
    }

    Vector<Optional<Table>> tables() const { return m_tables; }

    DotNETRuntime::MethodDef make_method(Schema::MethodDef const&);

    Table const find_table(TableId table_id) const
    {
        auto optional = m_tables[(int)table_id];
        if (!optional.has_value()) {
            warnln("Table {} does not exist", (int)table_id);
            VERIFY_NOT_REACHED();
        }
        return optional.value();
    }

    Vector<TableCell> read_row(TableIndex table_index)
    {
        return read_row(table_index.table, table_index.index_plus_one - 1);
    }

    Vector<TableCell> read_row(TableId table_id, int index)
    {
        auto& table = find_table(table_id);
        VERIFY(index >= 0 && (size_t)index < table.size);
        seek_row(table, index);
        Vector<TableCell> cells;
        for (auto& column : table.columns) {
            cells.append(read_cell(column));
        }
        return cells;
    }

    MethodDef read_entry_point();

    TokenValue resolve_token(u32 token)
    {
        auto msb = (int)(token >> 24);
        auto index = (int)(token & 0xFFFFFF);
        if (msb == 0x70) {
            reader.seek(m_us_stream.offset + index);
            auto len = IO::read_packed_int(reader);
            char buf[len];
            auto success = reader.read_or_error({ buf, len });
            VERIFY(success);
            if (buf[len - 1] == 0 || buf[len - 1] == 1)
                len--;
            return TokenValue { String { buf, len } };
        }
        auto cells = read_row((TableId)msb, index - 1);
        Row row {
            (TableId)msb,
            move(cells)
        };
        return TokenValue { row };
    }

private:
    MetadataReader(ByteBuffer const& buffer, PEImage image)
        : m_image(image)
    {
        // TODO clean this up.
        // Had to do this because the bytebuffer was being freed outside of the constructor.
        auto bytes = new u8[buffer.size()];
        memcpy(bytes, buffer.data(), buffer.size());
        reader = InputMemoryStream({ bytes, buffer.size() });

        auto start_offset = PEImage::resolve_virtual_address(m_image.sections, m_image.metadata.virtual_address);
        reader.seek(start_offset);
        READ_32(metadata_header)
        if (metadata_header != 0x424A5342) {
            warnln("Invalid metadata header. Expected 0x424A5342, got 0x{:08x}", metadata_header);
            VERIFY_NOT_REACHED();
        }
        SKIP(8)
        READ_32(runtime_version_length)
        READ_ZERO_TERMINATED_STRING(runtime_version, runtime_version_length)
        ALIGN4
        SKIP(2)
        READ_16(number_of_streams)

        Vector<HeapHeader> heap_headers;
        for (size_t i = 0; i < number_of_streams; i++) {
            READ_32(heap_offset)
            auto offset = start_offset + heap_offset;
            READ_32(size)
            READ_ALIGNED_STRING(name, 16)
            heap_headers.append(HeapHeader {
                .offset = offset,
                .size = size,
                .name = name,
            });
        }

        for (auto heap_header : heap_headers) {
            if (heap_header.name == "#-" || heap_header.name == "#~")
                m_table_stream = heap_header;
            if (heap_header.name == "#Strings")
                m_string_stream = heap_header;
            if (heap_header.name == "#US")
                m_us_stream = heap_header;
            if (heap_header.name == "#GUID")
                m_guid_stream = heap_header;
            if (heap_header.name == "#Blob")
                m_blob_stream = heap_header;
        }
        if (m_table_stream.name.is_empty() || m_string_stream.name.is_empty() || m_us_stream.name.is_empty() || m_guid_stream.name.is_empty() || m_blob_stream.name.is_empty()) {
            warnln("Could not find all the required heap headers");
            VERIFY_NOT_REACHED();
        }

        reader.seek(m_table_stream.offset);
        SKIP(6)
        READ_8(heap_sizes)
        SKIP(1)
        READ_64(valid_tables)
        READ_64(sorted_tables)

        auto string_index_size = (heap_sizes & 1) == 0 ? 2 : 4;
        auto guid_index_size = (heap_sizes & 2) == 0 ? 2 : 4;
        auto blob_index_size = (heap_sizes & 4) == 0 ? 2 : 4;

        for (size_t i = 0; i <= 63; i++) {
            if (((valid_tables >> i) & 1) == 0)
                m_row_counts.append(Optional<int> {});
            else {
                READ_32(row_count)
                m_row_counts.append((int)row_count);
            }
        }

        auto size_of_index = [](int n) {
            return n >= 0x10000 ? 4 : 2;
        };

        HashMap<int, int> coded_index_sizes;
        auto try_get = [](HashMap<int, int>& d, int key, Function<int()> const& init) {
            auto option = d.get(key);
            if (option.has_value())
                return option.value();
            else {
                int value = init();
                d.set(key, value);
                return value;
            }
        };

        auto coded_index_size = [&](CodedIndex const& i) {
            Function<int()> calc = [&]() {
                int max_value = NumericLimits<int>::min();
                for (auto table_id : i.tables) {
                    auto row_count_amount = row_count(table_id);
                    if (row_count_amount > max_value)
                        max_value = row_count_amount;
                }
                return size_of_index(max_value << i.bits);
            };
            return try_get(coded_index_sizes, (int)i.id, calc);
        };

        auto col_size = [&](Column const& col) {
            switch (col.value.type()) {
            case ColumnType::Int16:
                return 2;
            case ColumnType::Int32:
                return 4;
            case ColumnType::StringIndex:
                return string_index_size;
            case ColumnType::GuidIndex:
                return guid_index_size;
            case ColumnType::BlobIndex:
                return blob_index_size;
            case ColumnType::TableIndex:
                return size_of_index(row_count(col.value.table_index().table));
            case ColumnType::CodedIndex:
                return coded_index_size(col.value.coded_index());
            default:
                VERIFY_NOT_REACHED();
            }
        };

        auto table_position = reader.offset();

        auto make_table = [&](TableId const& id) {
            auto create_table = [&](const size_t row_count) {
                auto offset = table_position;
                Vector<ComputedColumn> cols;
                size_t row_size = 0;
                for (auto& c : SchemaUtils::table_columns(id)) {
                    ComputedColumn newColumn {
                        .name = c.name,
                        .value = c.value,
                        .size = col_size(c),
                    };
                    cols.append((ComputedColumn)newColumn);
                    row_size += newColumn.size;
                }
                auto table_size = row_size * row_count;
                table_position += table_size;
                return Table {
                    .id = id,
                    .row_count = row_count,
                    .row_size = row_size,
                    .offset = offset,
                    .size = table_size,
                    .isSorted = ((sorted_tables >> (int)id) & 1) != 0,
                    .columns = cols,
                };
            };
            auto option = m_row_counts[(size_t)id];
            if (option.has_value())
                return Optional<Table> { create_table(option.value()) };
            return Optional<Table> {};
        };
        for (size_t i = 0; i < 64; i++) {
            m_tables.append(make_table((TableId)i));
        }
    }

    static i32 cell_i32(TableCell& cell)
    {
        if (cell.type() == CellType::Int32)
            return cell.int32();
        if (cell.type() == CellType::Int16)
            return cell.int16();
        VERIFY_NOT_REACHED();
    }

    static String cell_str(TableCell& cell)
    {
        if (cell.type() == CellType::String)
            return cell.string();
        VERIFY_NOT_REACHED();
    }

    static ByteBuffer cell_blob(TableCell& cell)
    {
        if (cell.type() == CellType::Blob)
            return cell.blob();
        VERIFY_NOT_REACHED();
    }

    void seek_row(Table const& table, int index)
    {
        auto offset = table.offset + (index * table.row_size);
        reader.seek(offset);
    }

    Vector<LocalVar> resolve_local_vars(u32 token);

    MethodBody read_body_at(unsigned rva)
    {
        static HashMap<unsigned, MethodBody> cache;
        auto option = cache.get(rva);
        if (option.has_value())
            return option.value();
        auto body = read_body_impl(rva);
        cache.set(rva, body);
        return body;
    }

    MethodBody read_body_impl(unsigned rva)
    {
        auto offset = PEImage::resolve_virtual_address(m_image.sections, rva);
        reader.seek(offset);
        return MethodBody::read_method_body(reader);
    }

    Guid const read_guid(size_t i)
    {
        if (i == 0)
            return Guid {};
        reader.seek(m_guid_stream.offset);
        for (size_t j = 0; j < i - 1; j++) {
            auto success = reader.discard_or_error(16);
            VERIFY(success);
        }
        u8 buffer[16];
        auto success = reader.read_or_error({ buffer, 16 });
        VERIFY(success);
        return Guid {
            .a = ((int)buffer[3] << 24) | ((int)buffer[2] << 16) | ((int)buffer[1] << 8) | buffer[0],
            .b = (i16)(((int)buffer[5] << 8) | buffer[4]),
            .c = (i16)(((int)buffer[7] << 8) | buffer[6]),
            .d = buffer[8],
            .e = buffer[9],
            .f = buffer[10],
            .g = buffer[11],
            .h = buffer[12],
            .i = buffer[13],
            .j = buffer[14],
            .k = buffer[15],
        };
    }

    ByteBuffer const read_blob(size_t i)
    {
        reader.seek(m_blob_stream.offset + i);
        auto size = IO::read_packed_int(reader);
        auto buffer = MUST(ByteBuffer::create_uninitialized(size));
        auto success = reader.read_or_error({ buffer.data(), size });
        VERIFY(success);
        return buffer;
    }

    TableCell read_cell(ComputedColumn const& col)
    {
        int value;
        if (col.size == 2) {
            auto result = IO::read_u16(reader);
            VERIFY(result.has_value());
            value = result.value();
        } else {
            auto result = IO::read_u32(reader);
            VERIFY(result.has_value());
            value = result.value();
        }
        switch (col.value.type()) {
        case ColumnType::Int16:
            return TableCell { (short)value };
        case ColumnType::Int32:
            return TableCell { value };
        case ColumnType::StringIndex: {
            auto offset = reader.offset();
            auto result = read_string(value);
            reader.seek(offset);
            return TableCell { result };
        }
        case ColumnType::GuidIndex: {
            auto offset = reader.offset();
            auto result = read_guid(value);
            reader.seek(offset);
            return TableCell { result };
        }
        case ColumnType::BlobIndex: {
            auto offset = reader.offset();
            auto result = read_blob(value);
            reader.seek(offset);
            return TableCell { result };
        }
        case ColumnType::TableIndex:
            return TableCell { TableIndex { col.value.table_index().table, value } };
        case ColumnType::CodedIndex:
            return TableCell { CodedIndex::decode_coded_index(col.value.coded_index(), value) };
        default:
            VERIFY_NOT_REACHED();
        }
    }

    PEImage m_image;
    u8 tmp[0] = {};
    InputMemoryStream reader { { tmp, 0 } };
    Vector<Optional<int>, 64> m_row_counts;
    Vector<Optional<Table>, 64> m_tables;
    HeapHeader m_table_stream;
    HeapHeader m_string_stream;
    HeapHeader m_us_stream;
    HeapHeader m_guid_stream;
    HeapHeader m_blob_stream;
};
}
