/*
 * Copyright (c) 2021, Daniel Flaws <dflaws1@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#include "Object.h"
#include "Enums.h"
#include "Signature.h"

namespace DotNETRuntime {
Object::Object(Vector<Schema::Field> fields, String type_name)
    : m_type(type_name)
{
    for (auto& field : fields) {
        if ((field.Flags & (int)FieldAttributes::Static) != 0)
            continue;
        auto signature = TypeSignature::decode_type_signature(field.Signature);
        switch (signature->type) {
        case TypeSignature::Type::PrimitiveTypeSig:
            warnln("Init object field {}, flags: 0x{:02x}", field.Name, (u16)field.Flags);
            m_fields.set(field.Name, CLIVariantUtils::init_zeroed(signature->element_type));
            break;
        default:
            warnln("todo field type {}", (int)signature->type);
            TODO();
        }
    }
}

void Object::set_field(StringView field_name, CLIVariant value)
{
    auto it = m_fields.find(field_name);
    VERIFY(it != m_fields.end());
    m_fields.set(field_name, value);
}
}