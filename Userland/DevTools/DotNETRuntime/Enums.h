/*
 * Copyright (c) 2021, Daniel Flaws <dflaws1@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#pragma once

namespace DotNETRuntime {
enum class CodedIndexId {
    Invalid = -1,
    CustomAttributeType = 0,
    HasConstant = 1,
    HasCustomAttribute = 2,
    HasDeclSecurity = 3,
    HasFieldMarshal = 4,
    HasSemantics = 5,
    Implementation = 6,
    MemberForwarded = 7,
    MemberRefParent = 8,
    MethodDefOrRef = 9,
    ResolutionScope = 10,
    TypeDefOrRef = 11,
    TypeOrMethodDef = 12,
};

enum class TypeCode {
    Empty = 0,
    Object = 1,
    DBNull = 2,
    Boolean = 3,
    Char = 4,
    SByte = 5,
    Byte = 6,
    Int16 = 7,
    UInt16 = 8,
    Int32 = 9,
    UInt32 = 10,
    Int64 = 11,
    UInt64 = 12,
    Single = 13,
    Double = 14,
    Decimal = 15,
    DateTime = 16,
    String = 18,
};

enum class TargetArchitecture {
    I386 = 0x014c,
    AMD64 = 0x8664,
    IA64 = 0x0200,
    ARM = 0x01c0,
    ARMv7 = 0x01c4,
    ARM64 = 0xaa64,
    AC020 = 0xc020,
};

enum class ModuleKind {
    Dll = 0,
    Windows = 1,
    Console = 2,
};

enum class ModuleAttributes {
    ILOnly = 1,
    Required32Bit = 2,
    StrongNameSigned = 8,
    Preferred32Bit = 0x00020000,
};

enum class ModuleCharacteristics {
    HighEntropyVA = 0x0020,
    DynamicBase = 0x0040,
    NoSEH = 0x0400,
    NXCompat = 0x0100,
    AppContainer = 0x1000,
    TerminalServerAware = 0x8000,
};

enum class MethodAttributes {
    MemberAccessMask = 0x0007,
    PrivateScope = 0x0000,
    Private = 0x0001,
    FamANDAssem = 0x0002,
    Assembly = 0x0003,
    Family = 0x0004,
    FamORAssem = 0x0005,
    Public = 0x0006,
    Static = 0x0010,
    Final = 0x0020,
    Virtual = 0x0040,
    HideBySig = 0x0080,
    VtableLayoutMask = 0x0100,
    ReuseSlot = 0x0000,
    NewSlot = 0x0100,
    Abstract = 0x0400,
    SpecialName = 0x0800,
    PinvokeImpl = 0x2000,
    UnmanagedExport = 0x0008,
    RTSpecialName = 0x1000,
    ReservedMask = 0xd000,
    HasSecurity = 0x4000,
    RequireSecObject = 0x8000,
};

enum class MethodImplAttributes {
    CodeTypeMask = 0x0003,
    IL = 0x0000,
    Native = 0x0001,
    OPTIL = 0x0002,
    Runtime = 0x0003,
    ManagedMask = 0x0004,
    Unmanaged = 0x0004,
    Managed = 0x0000,
    ForwardRef = 0x0010,
    PreserveSig = 0x0080,
    InternalCall = 0x1000,
    Synchronized = 0x0020,
    NoInlining = 0x0008,
    MaxMethodImplVal = 0xffff,
    NoOptimization = 0x0040,
};

enum class FieldAttributes {
    FieldAccessMask = 0x0007,
    CompilerControlled = 0x0000,
    Private = 0x0001,
    FamANDAssem = 0x0002,
    Assembly = 0x0003,
    Family = 0x0004,
    FamORAssem = 0x0005,
    Public = 0x0006,
    Static = 0x0010,
    InitOnly = 0x0020,
    Literal = 0x0040,
    NotSerialized = 0x0080,
    SpecialName = 0x0200,
    PInvokeImpl = 0x2000,
    RTSpecialName = 0x0400,
    HasFieldMarshal = 0x1000,
    HasDefault = 0x8000,
    HasFieldRVA = 0x0100,
};

#define ENUMERATE_TABLE_IDS                                                      \
    __ENUMERATE_TABLE_ID(Assembly, 0x20, assembly)                               \
    __ENUMERATE_TABLE_ID(AssemblyOS, 0x22, assembly_os)                          \
    __ENUMERATE_TABLE_ID(AssemblyProcessor, 0x21, assembly_processor)            \
    __ENUMERATE_TABLE_ID(AssemblyRef, 0x23, assembly_ref)                        \
    __ENUMERATE_TABLE_ID(AssemblyRefOS, 0x25, assembly_ref_os)                   \
    __ENUMERATE_TABLE_ID(AssemblyRefProcessor, 0x24, assembly_ref_processor)     \
    __ENUMERATE_TABLE_ID(ClassLayout, 0x0F, class_layout)                        \
    __ENUMERATE_TABLE_ID(Constant, 0x0B, constant)                               \
    __ENUMERATE_TABLE_ID(CustomAttribute, 0x0C, custom_attribute)                \
    __ENUMERATE_TABLE_ID(DeclSecurity, 0x0E, decl_security)                      \
    __ENUMERATE_TABLE_ID(EventMap, 0x12, event_map)                              \
    __ENUMERATE_TABLE_ID(Event, 0x14, event)                                     \
    __ENUMERATE_TABLE_ID(ExportedType, 0x27, exported_type)                      \
    __ENUMERATE_TABLE_ID(Field, 0x04, field)                                     \
    __ENUMERATE_TABLE_ID(FieldLayout, 0x10, field_layout)                        \
    __ENUMERATE_TABLE_ID(FieldMarshal, 0x0D, field_marshal)                      \
    __ENUMERATE_TABLE_ID(FieldRVA, 0x1D, field_rva)                              \
    __ENUMERATE_TABLE_ID(File, 0x26, file)                                       \
    __ENUMERATE_TABLE_ID(GenericParam, 0x2A, generic_param)                      \
    __ENUMERATE_TABLE_ID(GenericParamConstraint, 0x2C, generic_param_constraint) \
    __ENUMERATE_TABLE_ID(ImplMap, 0x1C, impl_map)                                \
    __ENUMERATE_TABLE_ID(InterfaceImpl, 0x09, interface_impl)                    \
    __ENUMERATE_TABLE_ID(ManifestResource, 0x28, manifest_resource)              \
    __ENUMERATE_TABLE_ID(MemberRef, 0x0A, member_ref)                            \
    __ENUMERATE_TABLE_ID(MethodDef, 0x06, method_def)                            \
    __ENUMERATE_TABLE_ID(MethodImpl, 0x19, method_impl)                          \
    __ENUMERATE_TABLE_ID(MethodSemantics, 0x18, method_semantics)                \
    __ENUMERATE_TABLE_ID(MethodSpec, 0x2B, method_spec)                          \
    __ENUMERATE_TABLE_ID(Module, 0x00, module)                                   \
    __ENUMERATE_TABLE_ID(ModuleRef, 0x1A, module_ref)                            \
    __ENUMERATE_TABLE_ID(NestedClass, 0x29, nested_class)                        \
    __ENUMERATE_TABLE_ID(Param, 0x08, param)                                     \
    __ENUMERATE_TABLE_ID(Property, 0x17, property)                               \
    __ENUMERATE_TABLE_ID(PropertyMap, 0x15, property_map)                        \
    __ENUMERATE_TABLE_ID(StandAloneSig, 0x11, stand_alone_sig)                   \
    __ENUMERATE_TABLE_ID(TypeDef, 0x02, type_def)                                \
    __ENUMERATE_TABLE_ID(TypeRef, 0x01, type_ref)                                \
    __ENUMERATE_TABLE_ID(TypeSpec, 0x1B, type_spec)                              \
    __ENUMERATE_TABLE_ID(FieldPtr, 3, field_ptr)                                 \
    __ENUMERATE_TABLE_ID(MethodPtr, 5, method_ptr)                               \
    __ENUMERATE_TABLE_ID(ParamPtr, 7, param_ptr)                                 \
    __ENUMERATE_TABLE_ID(EventPtr, 19, event_ptr)                                \
    __ENUMERATE_TABLE_ID(PropertyPtr, 22, property_ptr)                          \
    __ENUMERATE_TABLE_ID(EncodingLog, 30, encoding_log)                          \
    __ENUMERATE_TABLE_ID(EncodingMap, 31, encoding_map)

enum class TableId {
#define __ENUMERATE_TABLE_ID(name, id, snake) name = id,
    ENUMERATE_TABLE_IDS
#undef __ENUMERATE_TABLE_ID
};

inline const char* table_id_to_string(TableId key)
{
    switch (key) {
#define __ENUMERATE_TABLE_ID(name, id, snake) \
    case TableId::name:                       \
        return #name;
        ENUMERATE_TABLE_IDS
#undef __ENUMERATE_TABLE_ID
    default:
        return nullptr;
    }
}

#define ENUMERATE_INSTRUCTION_CODES                   \
    __ENUMERATE_INSTRUCTION_CODE(Nop, 0)              \
    __ENUMERATE_INSTRUCTION_CODE(Break, 1)            \
    __ENUMERATE_INSTRUCTION_CODE(Ldarg_0, 2)          \
    __ENUMERATE_INSTRUCTION_CODE(Ldarg_1, 3)          \
    __ENUMERATE_INSTRUCTION_CODE(Ldarg_2, 4)          \
    __ENUMERATE_INSTRUCTION_CODE(Ldarg_3, 5)          \
    __ENUMERATE_INSTRUCTION_CODE(Ldloc_0, 6)          \
    __ENUMERATE_INSTRUCTION_CODE(Ldloc_1, 7)          \
    __ENUMERATE_INSTRUCTION_CODE(Ldloc_2, 8)          \
    __ENUMERATE_INSTRUCTION_CODE(Ldloc_3, 9)          \
    __ENUMERATE_INSTRUCTION_CODE(Stloc_0, 10)         \
    __ENUMERATE_INSTRUCTION_CODE(Stloc_1, 11)         \
    __ENUMERATE_INSTRUCTION_CODE(Stloc_2, 12)         \
    __ENUMERATE_INSTRUCTION_CODE(Stloc_3, 13)         \
    __ENUMERATE_INSTRUCTION_CODE(Ldarg_S, 14)         \
    __ENUMERATE_INSTRUCTION_CODE(Ldarga_S, 15)        \
    __ENUMERATE_INSTRUCTION_CODE(Starg_S, 16)         \
    __ENUMERATE_INSTRUCTION_CODE(Ldloc_S, 17)         \
    __ENUMERATE_INSTRUCTION_CODE(Ldloca_S, 18)        \
    __ENUMERATE_INSTRUCTION_CODE(Stloc_S, 19)         \
    __ENUMERATE_INSTRUCTION_CODE(Ldnull, 20)          \
    __ENUMERATE_INSTRUCTION_CODE(Ldc_I4_M1, 21)       \
    __ENUMERATE_INSTRUCTION_CODE(Ldc_I4_0, 22)        \
    __ENUMERATE_INSTRUCTION_CODE(Ldc_I4_1, 23)        \
    __ENUMERATE_INSTRUCTION_CODE(Ldc_I4_2, 24)        \
    __ENUMERATE_INSTRUCTION_CODE(Ldc_I4_3, 25)        \
    __ENUMERATE_INSTRUCTION_CODE(Ldc_I4_4, 26)        \
    __ENUMERATE_INSTRUCTION_CODE(Ldc_I4_5, 27)        \
    __ENUMERATE_INSTRUCTION_CODE(Ldc_I4_6, 28)        \
    __ENUMERATE_INSTRUCTION_CODE(Ldc_I4_7, 29)        \
    __ENUMERATE_INSTRUCTION_CODE(Ldc_I4_8, 30)        \
    __ENUMERATE_INSTRUCTION_CODE(Ldc_I4_S, 31)        \
    __ENUMERATE_INSTRUCTION_CODE(Ldc_I4, 32)          \
    __ENUMERATE_INSTRUCTION_CODE(Ldc_I8, 33)          \
    __ENUMERATE_INSTRUCTION_CODE(Ldc_R4, 34)          \
    __ENUMERATE_INSTRUCTION_CODE(Ldc_R8, 35)          \
    __ENUMERATE_INSTRUCTION_CODE(Dup, 37)             \
    __ENUMERATE_INSTRUCTION_CODE(Pop, 38)             \
    __ENUMERATE_INSTRUCTION_CODE(Jmp, 39)             \
    __ENUMERATE_INSTRUCTION_CODE(Call, 40)            \
    __ENUMERATE_INSTRUCTION_CODE(Calli, 41)           \
    __ENUMERATE_INSTRUCTION_CODE(Ret, 42)             \
    __ENUMERATE_INSTRUCTION_CODE(Br_S, 43)            \
    __ENUMERATE_INSTRUCTION_CODE(Brfalse_S, 44)       \
    __ENUMERATE_INSTRUCTION_CODE(Brtrue_S, 45)        \
    __ENUMERATE_INSTRUCTION_CODE(Beq_S, 46)           \
    __ENUMERATE_INSTRUCTION_CODE(Bge_S, 47)           \
    __ENUMERATE_INSTRUCTION_CODE(Bgt_S, 48)           \
    __ENUMERATE_INSTRUCTION_CODE(Ble_S, 49)           \
    __ENUMERATE_INSTRUCTION_CODE(Blt_S, 50)           \
    __ENUMERATE_INSTRUCTION_CODE(Bne_Un_S, 51)        \
    __ENUMERATE_INSTRUCTION_CODE(Bge_Un_S, 52)        \
    __ENUMERATE_INSTRUCTION_CODE(Bgt_Un_S, 53)        \
    __ENUMERATE_INSTRUCTION_CODE(Ble_Un_S, 54)        \
    __ENUMERATE_INSTRUCTION_CODE(Blt_Un_S, 55)        \
    __ENUMERATE_INSTRUCTION_CODE(Br, 56)              \
    __ENUMERATE_INSTRUCTION_CODE(Brfalse, 57)         \
    __ENUMERATE_INSTRUCTION_CODE(Brtrue, 58)          \
    __ENUMERATE_INSTRUCTION_CODE(Beq, 59)             \
    __ENUMERATE_INSTRUCTION_CODE(Bge, 60)             \
    __ENUMERATE_INSTRUCTION_CODE(Bgt, 61)             \
    __ENUMERATE_INSTRUCTION_CODE(Ble, 62)             \
    __ENUMERATE_INSTRUCTION_CODE(Blt, 63)             \
    __ENUMERATE_INSTRUCTION_CODE(Bne_Un, 64)          \
    __ENUMERATE_INSTRUCTION_CODE(Bge_Un, 65)          \
    __ENUMERATE_INSTRUCTION_CODE(Bgt_Un, 66)          \
    __ENUMERATE_INSTRUCTION_CODE(Ble_Un, 67)          \
    __ENUMERATE_INSTRUCTION_CODE(Blt_Un, 68)          \
    __ENUMERATE_INSTRUCTION_CODE(Switch, 69)          \
    __ENUMERATE_INSTRUCTION_CODE(Ldind_I1, 70)        \
    __ENUMERATE_INSTRUCTION_CODE(Ldind_U1, 71)        \
    __ENUMERATE_INSTRUCTION_CODE(Ldind_I2, 72)        \
    __ENUMERATE_INSTRUCTION_CODE(Ldind_U2, 73)        \
    __ENUMERATE_INSTRUCTION_CODE(Ldind_I4, 74)        \
    __ENUMERATE_INSTRUCTION_CODE(Ldind_U4, 75)        \
    __ENUMERATE_INSTRUCTION_CODE(Ldind_I8, 76)        \
    __ENUMERATE_INSTRUCTION_CODE(Ldind_I, 77)         \
    __ENUMERATE_INSTRUCTION_CODE(Ldind_R4, 78)        \
    __ENUMERATE_INSTRUCTION_CODE(Ldind_R8, 79)        \
    __ENUMERATE_INSTRUCTION_CODE(Ldind_Ref, 80)       \
    __ENUMERATE_INSTRUCTION_CODE(Stind_Ref, 81)       \
    __ENUMERATE_INSTRUCTION_CODE(Stind_I1, 82)        \
    __ENUMERATE_INSTRUCTION_CODE(Stind_I2, 83)        \
    __ENUMERATE_INSTRUCTION_CODE(Stind_I4, 84)        \
    __ENUMERATE_INSTRUCTION_CODE(Stind_I8, 85)        \
    __ENUMERATE_INSTRUCTION_CODE(Stind_R4, 86)        \
    __ENUMERATE_INSTRUCTION_CODE(Stind_R8, 87)        \
    __ENUMERATE_INSTRUCTION_CODE(Add, 88)             \
    __ENUMERATE_INSTRUCTION_CODE(Sub, 89)             \
    __ENUMERATE_INSTRUCTION_CODE(Mul, 90)             \
    __ENUMERATE_INSTRUCTION_CODE(Div, 91)             \
    __ENUMERATE_INSTRUCTION_CODE(Div_Un, 92)          \
    __ENUMERATE_INSTRUCTION_CODE(Rem, 93)             \
    __ENUMERATE_INSTRUCTION_CODE(Rem_Un, 94)          \
    __ENUMERATE_INSTRUCTION_CODE(And, 95)             \
    __ENUMERATE_INSTRUCTION_CODE(Or, 96)              \
    __ENUMERATE_INSTRUCTION_CODE(Xor, 97)             \
    __ENUMERATE_INSTRUCTION_CODE(Shl, 98)             \
    __ENUMERATE_INSTRUCTION_CODE(Shr, 99)             \
    __ENUMERATE_INSTRUCTION_CODE(Shr_Un, 100)         \
    __ENUMERATE_INSTRUCTION_CODE(Neg, 101)            \
    __ENUMERATE_INSTRUCTION_CODE(Not, 102)            \
    __ENUMERATE_INSTRUCTION_CODE(Conv_I1, 103)        \
    __ENUMERATE_INSTRUCTION_CODE(Conv_I2, 104)        \
    __ENUMERATE_INSTRUCTION_CODE(Conv_I4, 105)        \
    __ENUMERATE_INSTRUCTION_CODE(Conv_I8, 106)        \
    __ENUMERATE_INSTRUCTION_CODE(Conv_R4, 107)        \
    __ENUMERATE_INSTRUCTION_CODE(Conv_R8, 108)        \
    __ENUMERATE_INSTRUCTION_CODE(Conv_U4, 109)        \
    __ENUMERATE_INSTRUCTION_CODE(Conv_U8, 110)        \
    __ENUMERATE_INSTRUCTION_CODE(Callvirt, 111)       \
    __ENUMERATE_INSTRUCTION_CODE(Cpobj, 112)          \
    __ENUMERATE_INSTRUCTION_CODE(Ldobj, 113)          \
    __ENUMERATE_INSTRUCTION_CODE(Ldstr, 114)          \
    __ENUMERATE_INSTRUCTION_CODE(Newobj, 115)         \
    __ENUMERATE_INSTRUCTION_CODE(Castclass, 116)      \
    __ENUMERATE_INSTRUCTION_CODE(Isinst, 117)         \
    __ENUMERATE_INSTRUCTION_CODE(Conv_R_Un, 118)      \
    __ENUMERATE_INSTRUCTION_CODE(Unbox, 121)          \
    __ENUMERATE_INSTRUCTION_CODE(Throw, 122)          \
    __ENUMERATE_INSTRUCTION_CODE(Ldfld, 123)          \
    __ENUMERATE_INSTRUCTION_CODE(Ldflda, 124)         \
    __ENUMERATE_INSTRUCTION_CODE(Stfld, 125)          \
    __ENUMERATE_INSTRUCTION_CODE(Ldsfld, 126)         \
    __ENUMERATE_INSTRUCTION_CODE(Ldsflda, 127)        \
    __ENUMERATE_INSTRUCTION_CODE(Stsfld, 128)         \
    __ENUMERATE_INSTRUCTION_CODE(Stobj, 129)          \
    __ENUMERATE_INSTRUCTION_CODE(Conv_Ovf_I1_Un, 130) \
    __ENUMERATE_INSTRUCTION_CODE(Conv_Ovf_I2_Un, 131) \
    __ENUMERATE_INSTRUCTION_CODE(Conv_Ovf_I4_Un, 132) \
    __ENUMERATE_INSTRUCTION_CODE(Conv_Ovf_I8_Un, 133) \
    __ENUMERATE_INSTRUCTION_CODE(Conv_Ovf_U1_Un, 134) \
    __ENUMERATE_INSTRUCTION_CODE(Conv_Ovf_U2_Un, 135) \
    __ENUMERATE_INSTRUCTION_CODE(Conv_Ovf_U4_Un, 136) \
    __ENUMERATE_INSTRUCTION_CODE(Conv_Ovf_U8_Un, 137) \
    __ENUMERATE_INSTRUCTION_CODE(Conv_Ovf_I_Un, 138)  \
    __ENUMERATE_INSTRUCTION_CODE(Conv_Ovf_U_Un, 139)  \
    __ENUMERATE_INSTRUCTION_CODE(Box, 140)            \
    __ENUMERATE_INSTRUCTION_CODE(Newarr, 141)         \
    __ENUMERATE_INSTRUCTION_CODE(Ldlen, 142)          \
    __ENUMERATE_INSTRUCTION_CODE(Ldelema, 143)        \
    __ENUMERATE_INSTRUCTION_CODE(Ldelem_I1, 144)      \
    __ENUMERATE_INSTRUCTION_CODE(Ldelem_U1, 145)      \
    __ENUMERATE_INSTRUCTION_CODE(Ldelem_I2, 146)      \
    __ENUMERATE_INSTRUCTION_CODE(Ldelem_U2, 147)      \
    __ENUMERATE_INSTRUCTION_CODE(Ldelem_I4, 148)      \
    __ENUMERATE_INSTRUCTION_CODE(Ldelem_U4, 149)      \
    __ENUMERATE_INSTRUCTION_CODE(Ldelem_I8, 150)      \
    __ENUMERATE_INSTRUCTION_CODE(Ldelem_I, 151)       \
    __ENUMERATE_INSTRUCTION_CODE(Ldelem_R4, 152)      \
    __ENUMERATE_INSTRUCTION_CODE(Ldelem_R8, 153)      \
    __ENUMERATE_INSTRUCTION_CODE(Ldelem_Ref, 154)     \
    __ENUMERATE_INSTRUCTION_CODE(Stelem_I, 155)       \
    __ENUMERATE_INSTRUCTION_CODE(Stelem_I1, 156)      \
    __ENUMERATE_INSTRUCTION_CODE(Stelem_I2, 157)      \
    __ENUMERATE_INSTRUCTION_CODE(Stelem_I4, 158)      \
    __ENUMERATE_INSTRUCTION_CODE(Stelem_I8, 159)      \
    __ENUMERATE_INSTRUCTION_CODE(Stelem_R4, 160)      \
    __ENUMERATE_INSTRUCTION_CODE(Stelem_R8, 161)      \
    __ENUMERATE_INSTRUCTION_CODE(Stelem_Ref, 162)     \
    __ENUMERATE_INSTRUCTION_CODE(Ldelem, 163)         \
    __ENUMERATE_INSTRUCTION_CODE(Stelem, 164)         \
    __ENUMERATE_INSTRUCTION_CODE(Unbox_Any, 165)      \
    __ENUMERATE_INSTRUCTION_CODE(Conv_Ovf_I1, 179)    \
    __ENUMERATE_INSTRUCTION_CODE(Conv_Ovf_U1, 180)    \
    __ENUMERATE_INSTRUCTION_CODE(Conv_Ovf_I2, 181)    \
    __ENUMERATE_INSTRUCTION_CODE(Conv_Ovf_U2, 182)    \
    __ENUMERATE_INSTRUCTION_CODE(Conv_Ovf_I4, 183)    \
    __ENUMERATE_INSTRUCTION_CODE(Conv_Ovf_U4, 184)    \
    __ENUMERATE_INSTRUCTION_CODE(Conv_Ovf_I8, 185)    \
    __ENUMERATE_INSTRUCTION_CODE(Conv_Ovf_U8, 186)    \
    __ENUMERATE_INSTRUCTION_CODE(Refanyval, 194)      \
    __ENUMERATE_INSTRUCTION_CODE(Ckfinite, 195)       \
    __ENUMERATE_INSTRUCTION_CODE(Mkrefany, 198)       \
    __ENUMERATE_INSTRUCTION_CODE(Ldtoken, 208)        \
    __ENUMERATE_INSTRUCTION_CODE(Conv_U2, 209)        \
    __ENUMERATE_INSTRUCTION_CODE(Conv_U1, 210)        \
    __ENUMERATE_INSTRUCTION_CODE(Conv_I, 211)         \
    __ENUMERATE_INSTRUCTION_CODE(Conv_Ovf_I, 212)     \
    __ENUMERATE_INSTRUCTION_CODE(Conv_Ovf_U, 213)     \
    __ENUMERATE_INSTRUCTION_CODE(Add_Ovf, 214)        \
    __ENUMERATE_INSTRUCTION_CODE(Add_Ovf_Un, 215)     \
    __ENUMERATE_INSTRUCTION_CODE(Mul_Ovf, 216)        \
    __ENUMERATE_INSTRUCTION_CODE(Mul_Ovf_Un, 217)     \
    __ENUMERATE_INSTRUCTION_CODE(Sub_Ovf, 218)        \
    __ENUMERATE_INSTRUCTION_CODE(Sub_Ovf_Un, 219)     \
    __ENUMERATE_INSTRUCTION_CODE(Endfinally, 220)     \
    __ENUMERATE_INSTRUCTION_CODE(Leave, 221)          \
    __ENUMERATE_INSTRUCTION_CODE(Leave_S, 222)        \
    __ENUMERATE_INSTRUCTION_CODE(Stind_I, 223)        \
    __ENUMERATE_INSTRUCTION_CODE(Conv_U, 224)         \
    __ENUMERATE_INSTRUCTION_CODE(Prefix7, 248)        \
    __ENUMERATE_INSTRUCTION_CODE(Prefix6, 249)        \
    __ENUMERATE_INSTRUCTION_CODE(Prefix5, 250)        \
    __ENUMERATE_INSTRUCTION_CODE(Prefix4, 251)        \
    __ENUMERATE_INSTRUCTION_CODE(Prefix3, 252)        \
    __ENUMERATE_INSTRUCTION_CODE(Prefix2, 253)        \
    __ENUMERATE_INSTRUCTION_CODE(Prefix1, 254)        \
    __ENUMERATE_INSTRUCTION_CODE(Prefixref, 255)      \
    __ENUMERATE_INSTRUCTION_CODE(Arglist, -512)       \
    __ENUMERATE_INSTRUCTION_CODE(Ceq, -511)           \
    __ENUMERATE_INSTRUCTION_CODE(Cgt, -510)           \
    __ENUMERATE_INSTRUCTION_CODE(Cgt_Un, -509)        \
    __ENUMERATE_INSTRUCTION_CODE(Clt, -508)           \
    __ENUMERATE_INSTRUCTION_CODE(Clt_Un, -507)        \
    __ENUMERATE_INSTRUCTION_CODE(Ldftn, -506)         \
    __ENUMERATE_INSTRUCTION_CODE(Ldvirtftn, -505)     \
    __ENUMERATE_INSTRUCTION_CODE(Ldarg, -503)         \
    __ENUMERATE_INSTRUCTION_CODE(Ldarga, -502)        \
    __ENUMERATE_INSTRUCTION_CODE(Starg, -501)         \
    __ENUMERATE_INSTRUCTION_CODE(Ldloc, -500)         \
    __ENUMERATE_INSTRUCTION_CODE(Ldloca, -499)        \
    __ENUMERATE_INSTRUCTION_CODE(Stloc, -498)         \
    __ENUMERATE_INSTRUCTION_CODE(Localloc, -497)      \
    __ENUMERATE_INSTRUCTION_CODE(Endfilter, -495)     \
    __ENUMERATE_INSTRUCTION_CODE(Unaligned, -494)     \
    __ENUMERATE_INSTRUCTION_CODE(Volatile, -493)      \
    __ENUMERATE_INSTRUCTION_CODE(Tailcall, -492)      \
    __ENUMERATE_INSTRUCTION_CODE(Initobj, -491)       \
    __ENUMERATE_INSTRUCTION_CODE(Constrained, -490)   \
    __ENUMERATE_INSTRUCTION_CODE(Cpblk, -489)         \
    __ENUMERATE_INSTRUCTION_CODE(Initblk, -488)       \
    __ENUMERATE_INSTRUCTION_CODE(Rethrow, -486)       \
    __ENUMERATE_INSTRUCTION_CODE(Sizeof, -484)        \
    __ENUMERATE_INSTRUCTION_CODE(Refanytype, -483)    \
    __ENUMERATE_INSTRUCTION_CODE(Readonly, -482)

enum class InstructionCode {
#define __ENUMERATE_INSTRUCTION_CODE(name, id) name = id,
    ENUMERATE_INSTRUCTION_CODES
#undef __ENUMERATE_INSTRUCTION_CODE
};

inline const char* instruction_code_to_string(InstructionCode key)
{
    switch (key) {
#define __ENUMERATE_INSTRUCTION_CODE(name, id) \
    case InstructionCode::name:                \
        return #name;
        ENUMERATE_INSTRUCTION_CODES
#undef __ENUMERATE_INSTRUCTION_CODE
    default:
        return nullptr;
    }
}

#define ELEMENT_TYPES                                     \
    __ENUMERATE_ELEMENT_TYPE(Invalid, -1)                 \
    __ENUMERATE_ELEMENT_TYPE(End, 0)                      \
    __ENUMERATE_ELEMENT_TYPE(Void, 1)                     \
    __ENUMERATE_ELEMENT_TYPE(Boolean, 2)                  \
    __ENUMERATE_ELEMENT_TYPE(Char, 3)                     \
    __ENUMERATE_ELEMENT_TYPE(Int8, 4)                     \
    __ENUMERATE_ELEMENT_TYPE(UInt8, 5)                    \
    __ENUMERATE_ELEMENT_TYPE(Int16, 6)                    \
    __ENUMERATE_ELEMENT_TYPE(UInt16, 7)                   \
    __ENUMERATE_ELEMENT_TYPE(Int32, 8)                    \
    __ENUMERATE_ELEMENT_TYPE(UInt32, 9)                   \
    __ENUMERATE_ELEMENT_TYPE(Int64, 10)                   \
    __ENUMERATE_ELEMENT_TYPE(UInt64, 11)                  \
    __ENUMERATE_ELEMENT_TYPE(Single, 12)                  \
    __ENUMERATE_ELEMENT_TYPE(Double, 13)                  \
    __ENUMERATE_ELEMENT_TYPE(String, 14)                  \
    __ENUMERATE_ELEMENT_TYPE(Ptr, 15)                     \
    __ENUMERATE_ELEMENT_TYPE(ByRef, 16)                   \
    __ENUMERATE_ELEMENT_TYPE(ValueType, 17)               \
    __ENUMERATE_ELEMENT_TYPE(Class, 18)                   \
    __ENUMERATE_ELEMENT_TYPE(Var, 19)                     \
    __ENUMERATE_ELEMENT_TYPE(Array, 20)                   \
    __ENUMERATE_ELEMENT_TYPE(GenericInstantiation, 21)    \
    __ENUMERATE_ELEMENT_TYPE(TypedReference, 22)          \
    __ENUMERATE_ELEMENT_TYPE(IntPtr, 24)                  \
    __ENUMERATE_ELEMENT_TYPE(UIntPtr, 25)                 \
    __ENUMERATE_ELEMENT_TYPE(MethodPtr, 27)               \
    __ENUMERATE_ELEMENT_TYPE(Object, 28)                  \
    __ENUMERATE_ELEMENT_TYPE(ArraySz, 29)                 \
    __ENUMERATE_ELEMENT_TYPE(MethodVar, 30)               \
    __ENUMERATE_ELEMENT_TYPE(RequiredModifier, 31)        \
    __ENUMERATE_ELEMENT_TYPE(OptionalModifier, 32)        \
    __ENUMERATE_ELEMENT_TYPE(Internal, 33)                \
    __ENUMERATE_ELEMENT_TYPE(ElementTypeModifier, 0x40)   \
    __ENUMERATE_ELEMENT_TYPE(Sentinel, 0x41)              \
    __ENUMERATE_ELEMENT_TYPE(Pinned, 0x45)                \
    __ENUMERATE_ELEMENT_TYPE(R4_HFA, 0x46)                \
    __ENUMERATE_ELEMENT_TYPE(R8_HFA, 0x47)                \
    __ENUMERATE_ELEMENT_TYPE(CustomArgsType, 0x50)        \
    __ENUMERATE_ELEMENT_TYPE(CustomArgsBoxedObject, 0x51) \
    __ENUMERATE_ELEMENT_TYPE(CustomArgsField, 0x53)       \
    __ENUMERATE_ELEMENT_TYPE(CustomArgsProperty, 0x54)    \
    __ENUMERATE_ELEMENT_TYPE(CustomArgsEnum, 0x55)

#define __ENUMERATE_ELEMENT_TYPE(name, value) \
    name = value,
enum class ElementType {
    ELEMENT_TYPES
};
#undef __ENUMERATE_ELEMENT_TYPE
}
