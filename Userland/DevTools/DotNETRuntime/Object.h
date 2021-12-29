/*
 * Copyright (c) 2021, Daniel Flaws <dflaws1@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#pragma once

#include "Heap/Cell.h"
#include "Schema.h"
#include "Variant.h"
#include <AK/HashMap.h>
#include <AK/String.h>

namespace DotNETRuntime {
class Object : public Cell {
public:
    explicit Object(Vector<Schema::Field> fields, String type_name);
    void set_field(StringView field_name, CLIVariant value);
    virtual const char* class_name() const override { return m_type.characters(); }

private:
    HashMap<String, CLIVariant> m_fields;
    String m_type;
};

}
