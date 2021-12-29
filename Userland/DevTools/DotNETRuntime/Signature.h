/*
 * Copyright (c) 2021, Daniel Flaws <dflaws1@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#pragma once

#include "Enums.h"
#include "Forward.h"
#include "MetadataReader.h"
#include "MethodSignature.h"
#include "Types.h"
#include <AK/NonnullRefPtrVector.h>
#include <AK/String.h>
#include <AK/Types.h>
#include <AK/Vector.h>

namespace DotNETRuntime {
enum class CallingConventions {
    Standard = 0x0001,
    VarArgs = 0x0002,
    Any = Standard | VarArgs,
    HasThis = 0x0020,
    ExplicitThis = 0x0040,
};

enum class SignatureKind {
    Method = 0x00,
    Field = 0x06,
    LocalVars = 0x07,
    Property = 0x08,
};

enum class SignatureFlags {
    GENERIC = 0x10,
    HASTHIS = 0x20,
    EXPLICITTHIS = 0x40,
    DEFAULT = 0x00,
    C = 0x01,
    STDCALL = 0x02,
    THISCALL = 0x03,
    FASTCALL = 0x04,
    VARARG = 0x05,
    FIELD = 0x06,
    LOCAL = 0x07,
    PROPERTY = 0x08,
    TYPEMASK = 0xF,
};

struct ArrayShape {
    u32 rank { 0 };
    Vector<int> sizes;
    Vector<int> lo_bounds;

    bool operator==(ArrayShape const& other) const
    {
        return rank == other.rank && sizes == other.sizes && lo_bounds == other.lo_bounds;
    }
};

static ArrayShape s_array_zero_size_shape = {};

struct TypeSignature : public RefCounted<TypeSignature> {
    MethodSignature method_signature;
    ElementType element_type { ElementType::Invalid };
    RefPtr<TypeSignature> type_signature;
    NonnullRefPtrVector<TypeSignature> type_signature_array;
    TableIndex table_index;
    int generic_var { 0 };
    ArrayShape array_shape;

    enum class Type {
        PrimitiveTypeSig,
        RefTypeSig,
        TypeIndexSig,
        ArrayTypeSig,
        MethodPtrTypeSig,
        TypeGenericVar,
        MethodGenericVar,
        GenericInstantiationTypeSig,
        ModifierTypeSig,
        PinnedTypeSig,
    };

#define __ENUMERATE_ELEMENT_TYPE(name, value) \
    case ElementType::name:                   \
        return #name;
    static String element_type_to_string(ElementType element_type)
    {
        switch (element_type) {
            ELEMENT_TYPES
        default:
            VERIFY_NOT_REACHED();
        }
    }
#undef __ENUMERATE_ELEMENT_TYPE

    Type type;

    static NonnullRefPtr<TypeSignature> primitive_type_sig(ElementType element_type)
    {
        auto sig = construct();
        sig->element_type = element_type;
        sig->type = Type::PrimitiveTypeSig;
        return sig;
    }

    static NonnullRefPtr<TypeSignature> ref_type_sig(ElementType element_type, TypeSignature const& type_signature)
    {
        auto sig = construct();
        sig->element_type = element_type;
        sig->type_signature = type_signature;
        sig->type = Type::RefTypeSig;
        return sig;
    }

    static NonnullRefPtr<TypeSignature> type_index_sig(ElementType element_type, TableIndex table_index)
    {
        auto sig = construct();
        sig->element_type = element_type;
        sig->table_index = table_index;
        sig->type = Type::TypeIndexSig;
        return sig;
    }

    static NonnullRefPtr<TypeSignature> array_type_sig(TypeSignature const& type_signature, ArrayShape array_shape)
    {
        auto sig = construct();
        sig->type_signature = type_signature;
        sig->array_shape = array_shape;
        sig->type = Type::ArrayTypeSig;
        return sig;
    }

    static NonnullRefPtr<TypeSignature> method_ptr_type_sig(MethodSignature const& method_signature);

    static NonnullRefPtr<TypeSignature> type_generic_var(int t)
    {
        auto sig = construct();
        sig->generic_var = t;
        sig->type = Type::TypeGenericVar;
        return sig;
    }

    static NonnullRefPtr<TypeSignature> method_generic_var(int t)
    {
        auto sig = construct();
        sig->generic_var = t;
        sig->type = Type::MethodGenericVar;
        return sig;
    }

    static NonnullRefPtr<TypeSignature> generic_instantiation_type_sig(TypeSignature const& type_signature, NonnullRefPtrVector<TypeSignature> type_signature_array)
    {
        auto sig = construct();
        sig->type_signature = type_signature;
        sig->type_signature_array = type_signature_array;
        sig->type = Type::GenericInstantiationTypeSig;
        return sig;
    }

    static NonnullRefPtr<TypeSignature> modifier_type_sig(ElementType element_type, TableIndex table_index, TypeSignature const& type_signature)
    {
        auto sig = construct();
        sig->element_type = element_type;
        sig->table_index = table_index;
        sig->type_signature = type_signature;
        sig->type = Type::ModifierTypeSig;
        return sig;
    }

    static NonnullRefPtr<TypeSignature> pinned_type_sig(ElementType element_type, TypeSignature const& type_signature)
    {
        auto sig = construct();
        sig->element_type = element_type;
        sig->type_signature = type_signature;
        sig->type = Type::PinnedTypeSig;
        return sig;
    }

    static NonnullRefPtr<TypeSignature> construct() { return adopt_ref(*new TypeSignature); };

    String dump(MetadataReader&) const;

    static MethodSignature decode_method_signature(InputMemoryStream& reader);
    static MethodSignature decode_method_signature(ByteBuffer bytes);

    static NonnullRefPtr<TypeSignature> decode_type_signature(InputMemoryStream& reader);
    static NonnullRefPtr<TypeSignature> decode_type_signature(ByteBuffer bytes);

    bool operator==(TypeSignature const& other) const;

    ~TypeSignature();

private:
    TypeSignature();
};

}
