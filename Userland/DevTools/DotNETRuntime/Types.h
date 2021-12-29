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
#include "MethodBody.h"
#include <AK/Function.h>
#include <AK/String.h>
#include <AK/Variant.h>
#include <assert.h>

namespace DotNETRuntime {
enum class ColumnType {
    Invalid,
    Int16,
    Int32,
    StringIndex,
    BlobIndex,
    GuidIndex,
    TableIndex,
    CodedIndex,
};

class ColumnValue {
public:
    short int16() const
    {
        VERIFY(m_type == ColumnType::Int16);
        return m_value.get<short>();
    }
    int int32() const
    {
        VERIFY(m_type == ColumnType::Int32);
        return m_value.get<int>();
    }
    int string_index() const
    {
        VERIFY(m_type == ColumnType::StringIndex);
        return m_value.get<int>();
    }
    int blob_index() const
    {
        VERIFY(m_type == ColumnType::BlobIndex);
        return m_value.get<int>();
    }
    int guid_index() const
    {
        VERIFY(m_type == ColumnType::GuidIndex);
        return m_value.get<int>();
    }
    TableIndex table_index() const
    {
        VERIFY(m_type == ColumnType::TableIndex);
        return m_value.get<TableIndex>();
    }
    CodedIndex coded_index() const
    {
        VERIFY(m_type == ColumnType::CodedIndex);
        return m_value.get<CodedIndex>();
    }
    explicit ColumnValue(short value)
        : m_type(ColumnType::Int16)
        , m_value(value)
    {
    }
    ColumnValue(ColumnType type, int value)
        : m_type(type)
        , m_value(value)
    {
    }
    explicit ColumnValue(TableIndex value)
        : m_type(ColumnType::TableIndex)
        , m_value(value)
    {
    }
    explicit ColumnValue(CodedIndex value)
        : m_type(ColumnType::CodedIndex)
        , m_value(value)
    {
    }

    ColumnValue()
        : m_type(ColumnType::Invalid)
        , m_value(0)
    {
    }

    ColumnType type() const { return m_type; }

private:
    using Value = AK::Variant<short, int, TableIndex, CodedIndex>;
    ColumnType m_type { ColumnType::Invalid };
    Value m_value { 0 };
};

enum class CellType {
    Invalid,
    Int16,
    Int32,
    String,
    Blob,
    Guid,
    TableIndex,
};

class TableCell {
public:
    short int16() const
    {
        VERIFY(m_type == CellType::Int16);
        return m_value.get<short>();
    }
    int int32() const
    {
        VERIFY(m_type == CellType::Int32);
        return m_value.get<int>();
    }
    String string() const
    {
        VERIFY(m_type == CellType::String);
        return m_value.get<String>();
    }
    ByteBuffer blob() const
    {
        VERIFY(m_type == CellType::Blob);
        return m_value.get<ByteBuffer>();
    }
    Guid guid() const
    {
        VERIFY(m_type == CellType::Guid);
        return m_value.get<Guid>();
    }
    TableIndex table() const
    {
        VERIFY(m_type == CellType::TableIndex);
        return m_value.get<TableIndex>();
    }
    explicit TableCell(short value)
        : m_type(CellType::Int16)
        , m_value(value)
    {
    }
    explicit TableCell(int value)
        : m_type(CellType::Int32)
        , m_value(value)
    {
    }
    explicit TableCell(String value)
        : m_type(CellType::String)
        , m_value(move(value))
    {
    }
    explicit TableCell(ByteBuffer value)
        : m_type(CellType::Blob)
        , m_value(move(value))
    {
    }
    explicit TableCell(Guid value)
        : m_type(CellType::Guid)
        , m_value(value)
    {
    }
    explicit TableCell(TableIndex value)
        : m_type(CellType::TableIndex)
        , m_value(value)
    {
    }

    String dump() const
    {
        switch (m_type) {
        case CellType::Int16:
            return String::formatted("i16 0x{:04x}", (u16)m_value.get<short>());
        case CellType::Int32:
            return String::formatted("i32 0x{:08x}", (u32)m_value.get<int>());
        case CellType::String:
            return String::formatted("string {}", m_value.get<String>());
        case CellType::Blob:
            return "blob";
        case CellType::Guid:
            return "Guid";
        case CellType::TableIndex: {
            auto index = m_value.get<TableIndex>();
            return String::formatted("TableId: {}, index: {}", table_id_to_string(index.table), index.index_plus_one);
        }
        default:
            VERIFY_NOT_REACHED();
        }
    }

    CellType type() const { return m_type; }

private:
    using Value = AK::Variant<short, int, String, ByteBuffer, Guid, TableIndex>;
    CellType m_type { CellType::Invalid };
    Value m_value { 0 };
};

struct Column {
    u32 index { 0 };
    String name;
    ColumnValue value;
};

struct ComputedColumn {
    String name;
    ColumnValue value;
    int size { 0 };
};

struct Table {
    TableId id;
    size_t row_count { 0 };
    size_t row_size { 0 };
    size_t offset { 0 };
    size_t size { 0 };
    bool isSorted { false };
    Vector<ComputedColumn> columns;
};

struct Row {
    TableId table;
    Vector<TableCell> cells;
};

struct TokenValue {
    TokenValue(String const& string)
        : m_is_string(true)
        , m_string(move(string))
        , m_row()
    {
    }
    TokenValue(Row& row)
        : m_is_string(false)
        , m_string()
        , m_row(move(row))
    {
    }

    bool is_string() const { return m_is_string; }
    bool is_row() const { return !m_is_string; }

    String const& string() const
    {
        VERIFY(is_string());
        return m_string;
    }

    Row const& row() const
    {
        VERIFY(is_row());
        return m_row;
    }

    TokenValue(TokenValue&& other)
        : m_is_string(other.m_is_string)
        , m_string(move(other.m_string))
        , m_row(move(other.m_row))
    {
    }

private:
    bool m_is_string { false };
    String m_string;
    Row m_row;
};
}
