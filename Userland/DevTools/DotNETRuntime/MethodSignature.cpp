/*
 * Copyright (c) 2021, Daniel Flaws <dflaws1@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "MethodSignature.h"
#include "Signature.h"
#include <AK/String.h>

namespace DotNETRuntime {
String MethodSignature::dump(MetadataReader& meta) const
{
    StringBuilder builder;
    for (auto& param : params) {
        builder.append("\n");
        builder.append(param.dump(meta));
    }
    return String::formatted("Method Signature: is_property: {}, return_type: ({}), params: ({})", is_property, return_type ? "void" : return_type->dump(meta), builder.to_string());
}

bool MethodSignature::operator==(MethodSignature const& other) const
{
    if (!!return_type != !!other.return_type || !(is_property == other.is_property && calling_conventions == other.calling_conventions && generic_param_count == other.generic_param_count && ((!return_type && !other.return_type) || *return_type == *other.return_type) && params.size() == other.params.size()))
        return false;
    for (size_t i = 0; i < params.size(); i++) {
        if (params[i] != other.params[i])
            return false;
    }

    return true;
}
}
