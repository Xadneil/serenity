/*
 * Copyright (c) 2021, Daniel Flaws <dflaws1@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#include "Signature.h"
#include "MethodSignature.h"

namespace DotNETRuntime {
TypeSignature::TypeSignature() { }
TypeSignature::~TypeSignature() { }

bool TypeSignature::operator==(TypeSignature const& other) const
{
    if (&other == this)
        return true;
    if (other.type != type)
        return false;

    switch (type) {
    case Type::PrimitiveTypeSig:
        return element_type == other.element_type;
    case Type::RefTypeSig:
        return element_type == other.element_type && *type_signature == *other.type_signature;
    case Type::TypeIndexSig:
        return element_type == other.element_type && table_index == other.table_index;
    case Type::ArrayTypeSig:
        return *type_signature == *other.type_signature && array_shape == other.array_shape;
    case Type::MethodPtrTypeSig:
        return method_signature == other.method_signature;
    case Type::TypeGenericVar:
    case Type::MethodGenericVar:
        return generic_var == other.generic_var;
    case Type::GenericInstantiationTypeSig:
        if (*type_signature != *other.type_signature || type_signature_array.size() != other.type_signature_array.size())
            return false;
        for (size_t i = 0; i < type_signature_array.size(); i++) {
            if (type_signature_array[i] != other.type_signature_array[i])
                return false;
        }
        return true;
    case Type::ModifierTypeSig:
        return element_type == other.element_type && table_index == other.table_index && *type_signature == *other.type_signature;
    case Type::PinnedTypeSig:
        return element_type == other.element_type && *type_signature == *other.type_signature;
    default:
        VERIFY_NOT_REACHED();
    }
}

String TypeSignature::dump(MetadataReader& meta) const
{
    switch (type) {
    case Type::PrimitiveTypeSig:
        return String::formatted("Primitive Type: {}", TypeSignature::element_type_to_string(element_type));
    case Type::RefTypeSig:
        return String::formatted("Element Type: {}, inner sig: ({})", TypeSignature::element_type_to_string(element_type), type_signature->dump(meta));
    case Type::TypeIndexSig:
        return String::formatted("Element Type: {}, table index: {}", TypeSignature::element_type_to_string(element_type), table_index.dump(meta));
    case Type::ArrayTypeSig:
        return String::formatted("Array of ({})", type_signature->dump(meta));
    case Type::MethodPtrTypeSig:
        return String::formatted("Method pointer: {}", method_signature.dump(meta));
    case Type::TypeGenericVar:
    case Type::MethodGenericVar:
        return String::formatted("Generic {}", generic_var);
    case Type::GenericInstantiationTypeSig: {
        StringBuilder builder;
        for (auto& param : type_signature_array) {
            builder.append("\n");
            builder.append(param.dump(meta));
        }
        return String::formatted("Generic Instantiation: {}, params: ({})", type_signature->dump(meta), builder.to_string());
    }
    case Type::ModifierTypeSig:
        return String::formatted("Modifier: element_type: {}, table index: {}, inner sig: ({})", TypeSignature::element_type_to_string(element_type), table_index.dump(meta), type_signature->dump(meta));
    case Type::PinnedTypeSig:
        return String::formatted("Pinned: element_type: {}, inner sig: ({})", TypeSignature::element_type_to_string(element_type), type_signature->dump(meta));
    default:
        VERIFY_NOT_REACHED();
    }
}

NonnullRefPtr<TypeSignature> TypeSignature::method_ptr_type_sig(MethodSignature const& method_signature)
{
    auto sig = construct();
    sig->method_signature = method_signature;
    sig->type = Type::MethodPtrTypeSig;
    return sig;
}

MethodSignature TypeSignature::decode_method_signature(ByteBuffer bytes)
{
    InputMemoryStream reader(bytes);
    return TypeSignature::decode_method_signature(reader);
}

MethodSignature TypeSignature::decode_method_signature(InputMemoryStream& reader)
{
    u8 flags;
    auto success = reader.read_or_error({ &flags, 1 });
    VERIFY(success);
    auto kind = flags & (int)SignatureFlags::TYPEMASK;
    bool is_method = kind == (int)SignatureFlags::PROPERTY || (kind >= (int)SignatureFlags::DEFAULT && kind <= (int)SignatureFlags::VARARG);
    VERIFY(is_method);
    auto generic_param_count = ((flags & (int)SignatureFlags::GENERIC) == 0) ? 0 : IO::read_packed_int(reader);
    auto param_count = IO::read_packed_int(reader);
    auto return_type = decode_type_signature(reader);
    NonnullRefPtrVector<TypeSignature> params;
    for (size_t i = 0; i < param_count; i++) {
        params.append(decode_type_signature(reader));
    }
    MethodSignature method_signature {
        .is_property = kind == (int)SignatureFlags::PROPERTY,
        .calling_conventions = (int)CallingConventions::Standard | ((flags & (int)SignatureFlags::HASTHIS) == 0 ? (int)CallingConventions::Standard : (int)CallingConventions::HasThis) | ((flags & (int)SignatureFlags::EXPLICITTHIS) == 0 ? (int)CallingConventions::Standard : (int)CallingConventions::ExplicitThis),
        .generic_param_count = generic_param_count,
        .return_type = return_type,
        .params = params,
    };
    return method_signature;
}

NonnullRefPtr<TypeSignature> TypeSignature::decode_type_signature(ByteBuffer bytes)
{
    InputMemoryStream reader(bytes);
    return TypeSignature::decode_type_signature(reader);
}

NonnullRefPtr<TypeSignature> TypeSignature::decode_type_signature(InputMemoryStream& reader)
{
    auto decode_type_def_or_ref = [](InputMemoryStream& reader) {
        auto token = IO::read_packed_int(reader);
        auto type_def_or_ref = CodedIndex::coded_index_map().get((int)CodedIndexId::TypeDefOrRef);
        return CodedIndex::decode_coded_index(type_def_or_ref.value(), token);
    };
    auto e = (ElementType)IO::read_packed_int(reader);
    switch (e) {
    case ElementType::End:
    case ElementType::Void:
    case ElementType::Boolean:
    case ElementType::Char:
    case ElementType::Int8:
    case ElementType::UInt8:
    case ElementType::Int16:
    case ElementType::UInt16:
    case ElementType::Int32:
    case ElementType::UInt32:
    case ElementType::Int64:
    case ElementType::UInt64:
    case ElementType::Single:
    case ElementType::Double:
    case ElementType::String:
    case ElementType::TypedReference:
    case ElementType::IntPtr:
    case ElementType::UIntPtr:
    case ElementType::Object:
        return TypeSignature::primitive_type_sig(e);

    case ElementType::Ptr:
    case ElementType::ByRef:
        return TypeSignature::ref_type_sig(e, decode_type_signature(reader));

    case ElementType::ValueType:
    case ElementType::Class:
    case ElementType::CustomArgsEnum:
        return TypeSignature::type_index_sig(e, decode_type_def_or_ref(reader));

    case ElementType::ArraySz:
        return TypeSignature::array_type_sig(decode_type_signature(reader), s_array_zero_size_shape);

    case ElementType::Array: {
        auto t = decode_type_signature(reader);
        auto rank = IO::read_packed_int(reader);

        auto read_array = [&](size_t size, Vector<int> dest) {
            for (size_t i = 0; i < size; i++) {
                dest.append(IO::read_packed_int(reader));
            }
        };

        auto size_count = IO::read_packed_int(reader);
        Vector<int> sizes;
        read_array(size_count, sizes);

        auto lo_bound_count = IO::read_packed_int(reader);
        Vector<int> lo_bounds;
        read_array(lo_bound_count, lo_bounds);
        return TypeSignature::array_type_sig(t, ArrayShape {
                                                    .rank = rank,
                                                    .sizes = sizes,
                                                    .lo_bounds = lo_bounds,
                                                });
    }

    case ElementType::Var:
        return TypeSignature::type_generic_var(IO::read_packed_int(reader));

    case ElementType::MethodVar:
        return TypeSignature::method_generic_var(IO::read_packed_int(reader));

    case ElementType::MethodPtr:
        return TypeSignature::method_ptr_type_sig(decode_method_signature(reader));

    case ElementType::GenericInstantiation: {
        auto t = decode_type_signature(reader);
        auto n = IO::read_packed_int(reader);
        NonnullRefPtrVector<TypeSignature> types;
        for (size_t i = 0; i < n; i++) {
            types.append(decode_type_signature(reader));
        }
        return TypeSignature::generic_instantiation_type_sig(t, types);
    }

    case ElementType::RequiredModifier:
    case ElementType::OptionalModifier: {
        auto i = decode_type_def_or_ref(reader);
        auto t = decode_type_signature(reader);
        return TypeSignature::modifier_type_sig(e, i, t);
    }

    case ElementType::Sentinel:
    case ElementType::Pinned:
        return TypeSignature::pinned_type_sig(e, decode_type_signature(reader));

    default:
        warnln("Unknown Element Type {}", (int)e);
        VERIFY_NOT_REACHED();
    }
}

}