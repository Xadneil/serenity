/*
 * Copyright (c) 2021, Daniel Flaws <dflaws1@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "Variant.h"
#include "Signature.h"

namespace DotNETRuntime {
CLIVariant CLIVariantUtils::init_zeroed(ElementType element_type)
{
    switch (element_type) {
    case ElementType::Boolean:
        return false;
    case ElementType::Char:
        return (char)0;
    case ElementType::Double:
        return 0.0;
    case ElementType::Int16:
        return (short)0;
    case ElementType::Int32:
        return 0;
    case ElementType::Int64:
        return 0ll;
    case ElementType::Int8:
        return (i8)0;
    case ElementType::Object:
    case ElementType::String:
        return null_variant;
    case ElementType::Single:
        return 0.0f;
    case ElementType::UInt16:
        return (u16)0;
    case ElementType::UInt32:
        return 0u;
    case ElementType::UInt64:
        return 0ull;
    case ElementType::UInt8:
        return (u8)0;
    default:
        warnln("unsupported field type {}", TypeSignature::element_type_to_string(element_type));
        VERIFY_NOT_REACHED();
    }
}
}