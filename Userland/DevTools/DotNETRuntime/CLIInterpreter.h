/*
 * Copyright (c) 2021, Daniel Flaws <dflaws1@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "Heap/Heap.h"
#include "MetadataReader.h"
#include "MethodDef.h"
#include "MethodSignature.h"
#include "Object.h"
#include "Schema.h"
#include "Signature.h"
#include "Variant.h"
#include <AK/StackInfo.h>

namespace DotNETRuntime {
struct CallContext {
    MethodDef method;
    u32 ip { 0 };
    Vector<CLIVariant> stack;
    Vector<CLIVariant> variables;
    Vector<CLIVariant> arguments;
    NonnullRefPtr<MetadataReader> assembly_metadata;

    CallContext(MethodDef method, Vector<CLIVariant> variables, Vector<CLIVariant> arguments, NonnullRefPtr<MetadataReader> assembly_metadata)
        : method(method)
        , variables(variables)
        , arguments(arguments)
        , assembly_metadata(assembly_metadata)
    {
    }
};

struct TypeLocation {
    Schema::TypeDef type;
    Table table;
    size_t index;
};

struct CLIInterpreter {
    NonnullRefPtr<MetadataReader> m_mscorlib;
    Vector<Schema::Field> m_string_fields;
    Heap m_heap;
    HashMap<String, Object*> m_string_cache;
    StackInfo m_stack_info;
    Vector<CallContext> call_stack;

    Object* new_string([[maybe_unused]] String string_value)
    {
        auto it = m_string_cache.find(string_value);
        if (it != m_string_cache.end())
            return it->value;
        auto* new_obj = m_heap.allocate<Object>(m_string_fields, "System.String");
        // auto* string_buffer = new char[string_value.length()];
        // memcpy(string_buffer, string_value.characters(), string_value.length());
        // new_obj->set_field("m_arrayLength", (int)string_value.length());
        // new_obj->set_field("m_stringLength", (int)string_value.length());
        // new_obj->set_field("m_firstChar", );
        m_string_cache.set(string_value, new_obj);
        TODO();
        return new_obj;
    }

    CallContext make_call(MethodDef const& method, Vector<CLIVariant> const& arguments, NonnullRefPtr<MetadataReader> reader)
    {
        Vector<CLIVariant> var_values;
        for (auto& v : method.local_vars) {
            switch (v.type->type) {
            case TypeSignature::Type::PrimitiveTypeSig:
                var_values.append(CLIVariantUtils::init_zeroed(v.type->element_type));
                break;
            case TypeSignature::Type::TypeIndexSig: {
                // auto table_index = v.type->table_index;
                // auto row = meta.read_row(table_index.table, table_index.index - 1);
                // warnln("Reading variable {}, type {}, element type {}, TableId {}", v.name, (int)v.type->type, (int)v.type->element_type, table_id_to_string(table_index.table));
                // for (auto& cell : row) {
                //     warnln(cell.dump());
                // }
                // TODO();
                var_values.append(null_variant);
                break;
            }
            default:
                warnln("method {} Attempting to send local variable {} of type {}", method.name, v.name, (int)v.type->type);
                TODO();
                break;
            }
        }
        CallContext context(
            method,
            var_values,
            arguments,
            reader);

        call_stack.append(context);
        return context;
    }

    static TypeLocation get_type_impl(MetadataReader& reader, String const& referenced_type_name, String const& referenced_type_namespace, String const& assembly_name, String const& file_name)
    {
        //TODO find better way to find type in other assembly
        auto type_table = reader.find_table(TableId::TypeDef);
        Schema::TypeDef found_type_def;
        size_t type_index;
        for (size_t i = 0; i < type_table.row_count; i++) {
            Schema::TypeDef type_def(reader.read_row(TableId::TypeDef, i));
            if (type_def.TypeName == referenced_type_name && type_def.TypeNamespace == referenced_type_namespace) {
                found_type_def = type_def;
                type_index = i;
                break;
            }
        }
        if (found_type_def.TypeName.is_empty()) {
            warnln("Referenced type {}.{} was not found in assembly {}, file {}.", referenced_type_namespace, referenced_type_name, assembly_name, file_name);
            VERIFY_NOT_REACHED();
        }
        return { found_type_def, type_table, type_index };
    }

    static TypeLocation get_type(MetadataReader& reader, Schema::TypeRef const& referenced_type, String const& assembly_name, String const& file_name)
    {
        return get_type_impl(reader, referenced_type.TypeName, referenced_type.TypeNamespace, assembly_name, file_name);
    }

    static CLIVariant conv_type_sig(CLIVariant const& source, TypeSignature const& signature)
    {
        if (signature.type != TypeSignature::Type::PrimitiveTypeSig)
            return source;
        switch (signature.element_type) {
        case ElementType::Boolean:
            if (!source.has<bool>())
                TODO();
            return source;
        case ElementType::Char:
        case ElementType::UInt8:
            if (!source.has<u8>())
                TODO();
            return source;
        case ElementType::Int8:
            if (!source.has<i8>())
                TODO();
            return source;
        case ElementType::Int16:
            if (!source.has<i16>())
                TODO();
            return source;
        case ElementType::UInt16:
            if (!source.has<u16>())
                TODO();
            return source;
        case ElementType::Int32:
            if (!source.has<i32>())
                TODO();
            return source;
        case ElementType::UInt32:
            if (!source.has<u32>())
                TODO();
            return source;
        case ElementType::Int64:
            if (!source.has<i64>())
                TODO();
            return source;
        case ElementType::UInt64:
            if (!source.has<u64>())
                TODO();
            return source;
        case ElementType::Single:
            if (!source.has<float>())
                TODO();
            return source;
        case ElementType::Double:
            if (!source.has<double>())
                TODO();
            return source;
        case ElementType::Object:
        case ElementType::String:
            if (!source.has<Object*>())
                TODO();
            return source;
        default:
            return source;
        }
    }

    CallContext eval(CallContext context)
    {
        auto meta = context.assembly_metadata;
        auto body = *context.method.body;
        auto next = [&]() { context.ip++; };
        auto go_to = [&](u32 target) {
            context.ip = target;
        };
        auto pop_val = [&context]() {
            return context.stack.take_last();
        };
        auto pop_args = [&pop_val](MethodSignature const& signature) {
            Vector<CLIVariant> args;
            args.resize(signature.params.size());
            ssize_t i = signature.params.size() - 1;
            while (i >= 0) {
                args[i] = conv_type_sig(pop_val(), signature.params[i]);
                i--;
            }
            return args;
        };

        auto data_u32 = [](InstructionOperand const& operand) {
            if (operand.type() == InstructionOperand::Type::Int32Operand)
                return (u32)operand.int_32_operand();
            if (operand.type() == InstructionOperand::Type::BranchTarget)
                return (u32)operand.branch_target();
            if (operand.type() == InstructionOperand::Type::Int64Operand) {
                VERIFY(operand.int_64_operand() <= NumericLimits<u32>::max());
                return (u32)operand.int_64_operand();
            }
            VERIFY_NOT_REACHED();
        };

        while (context.ip < body.code.size()) {
            auto& instruction = body.code[context.ip];
            outln("IL_{:04x}: executing {}", instruction.offset, instruction_code_to_string((InstructionCode)instruction.instruction_code));
            switch (instruction.instruction_code) {
            case InstructionCode::Nop:
                next();
                break;
            case InstructionCode::Call: {
                VERIFY(instruction.instruction_operand.type() == InstructionOperand::Type::MetadataToken);
                auto resolved_token = meta->resolve_token(instruction.instruction_operand.metadata_token());
                VERIFY(resolved_token.is_row());
                auto& row = resolved_token.row();

                switch (row.table) {
                case TableId::MethodDef: {
                    auto method = meta->make_method(Schema::MethodDef { row.cells });
                    auto args = pop_args(method.signature);
                    if ((method.flags & (int)MethodAttributes::Static) == 0) {
                        // pop `this` value
                        args.insert(0, pop_val());
                    }
                    eval(make_call(method, args, meta));
                    next();
                    break;
                }
                case TableId::MemberRef: {
                    Schema::MemberRef member_ref(row.cells);
                    auto member_signature = TypeSignature::decode_method_signature(member_ref.Signature);
                    warnln("Call: referenced method name: {}, signature:\n{}", member_ref.Name, member_signature.dump(meta));
                    auto class_row = meta->read_row(member_ref.Class);
                    switch (member_ref.Class.table) {
                    case TableId::MethodDef:
                    case TableId::ModuleRef:
                    case TableId::TypeDef:
                    case TableId::TypeSpec:
                        TODO();
                        break;
                    case TableId::TypeRef: {
                        // The class that defines the member is defined in another
                        // module. (Note that it is unusual, but valid, to use a TypeRef token when the
                        // member is defined in this same module, in which case, its TypeDef token can
                        // be used instead.)
                        Schema::TypeRef referenced_type(class_row);
                        auto resolution_scope_row = meta->read_row(referenced_type.ResolutionScope);
                        warnln("referenced type name: {}.{}", referenced_type.TypeNamespace, referenced_type.TypeName);
                        switch (referenced_type.ResolutionScope.table) {
                        case TableId::Module:
                        case TableId::ModuleRef:
                        case TableId::TypeRef:
                            TODO();
                            break;
                        case TableId::AssemblyRef: {
                            Schema::AssemblyRef referenced_assembly(resolution_scope_row);
                            warnln("loading referenced assembly: {}", referenced_assembly.Name);
                            //TODO: implement global assembly cache
                            String file_name;
                            RefPtr<MetadataReader> assembly_reader_tmp;
                            if (referenced_assembly.Name == "System.Drawing") {
                                file_name = "./System.Drawing.dll";
                                assembly_reader_tmp = MUST(MetadataReader::create_from_file(file_name));
                            } else if (referenced_assembly.Name == "mscorlib") {
                                file_name = "./mscorlib.dll";
                                assembly_reader_tmp = m_mscorlib;
                            } else
                                TODO();
                            auto assembly_reader = assembly_reader_tmp.release_nonnull();

                            auto referenced_type_def = get_type(assembly_reader, referenced_type, referenced_assembly.Name, file_name);
                            Schema::TypeDef found_type_def = referenced_type_def.type;
                            Table type_table = referenced_type_def.table;
                            size_t type_index = referenced_type_def.index;

                            auto method_table = assembly_reader->find_table(TableId::MethodDef);
                            size_t method_search_upper_bound;
                            if (type_index == type_table.row_count - 1)
                                method_search_upper_bound = method_table.row_count;
                            else {
                                Schema::TypeDef next_type_def(assembly_reader->read_row(TableId::TypeDef, type_index + 1));
                                method_search_upper_bound = next_type_def.MethodList.index_plus_one;
                            }

                            MethodDef referenced_method;
                            bool found = false;
                            for (size_t i = found_type_def.MethodList.index_plus_one - 1; i < method_search_upper_bound; i++) {
                                Schema::MethodDef method_def(assembly_reader->read_row(TableId::MethodDef, i));
                                if (method_def.Name == member_ref.Name) {
                                    auto method_sig = TypeSignature::decode_method_signature(method_def.Signature);
                                    if (method_sig == member_signature) {
                                        auto method = assembly_reader->make_method(method_def);
                                        if ((method.flags & (int)MethodAttributes::Static) != 0) {
                                            warnln("constructor is static.");
                                            VERIFY_NOT_REACHED();
                                        }
                                        referenced_method = method;
                                        found = true;
                                        break;
                                    }
                                }
                            }
                            if (!found) {
                                warnln("Referenced method not found on type {}.{}", referenced_type.TypeNamespace, referenced_type.TypeName);
                                VERIFY_NOT_REACHED();
                            }
                            auto args = pop_args(referenced_method.signature);
                            if ((referenced_method.flags & (int)MethodAttributes::Static) == 0) {
                                // pop `this` value
                                args.insert(0, pop_val());
                            }
                            eval(make_call(referenced_method, args, assembly_reader));
                            next();
                            break;
                        }
                        default:
                            VERIFY_NOT_REACHED();
                        }
                    } break;
                    default:
                        VERIFY_NOT_REACHED();
                    }
                    break;
                }
                case TableId::MethodSpec:
                    warnln("unimplemented method call: {}", table_id_to_string(row.table));
                    TODO();
                default:
                    VERIFY_NOT_REACHED();
                }
                break;
            }
            case InstructionCode::Br_S:
            case InstructionCode::Br:
                go_to(data_u32(instruction.instruction_operand));
                break;
            case InstructionCode::Ldstr: {
                VERIFY(instruction.instruction_operand.type() == InstructionOperand::Type::MetadataToken);
                auto token = meta->resolve_token(instruction.instruction_operand.metadata_token());
                VERIFY(token.is_string());
                auto* string_object = new_string(token.string());
                context.stack.append(string_object);
                next();
                break;
            }
            case InstructionCode::Ldc_R4: {
                VERIFY(instruction.instruction_operand.type() == InstructionOperand::Type::Float32Operand);
                context.stack.append(instruction.instruction_operand.float_32_operand());
                next();
                break;
            }
            case InstructionCode::Newobj: {
                VERIFY(instruction.instruction_operand.type() == InstructionOperand::Type::MetadataToken);
                auto token = meta->resolve_token(instruction.instruction_operand.metadata_token());
                VERIFY(token.is_row());
                auto row = token.row();
                VERIFY(row.table == TableId::MemberRef);
                Schema::MemberRef constructor(row.cells);
                auto constructor_signature = TypeSignature::decode_method_signature(constructor.Signature);
                warnln("Newobj: constructor name: {}, signature:\n{}", constructor.Name, constructor_signature.dump(meta));
                auto class_row = meta->read_row(constructor.Class);
                switch (constructor.Class.table) {
                case TableId::MethodDef:
                case TableId::ModuleRef:
                case TableId::TypeDef:
                case TableId::TypeSpec:
                    TODO();
                    break;
                case TableId::TypeRef: {
                    // The class that defines the member is defined in another
                    // module. (Note that it is unusual, but valid, to use a TypeRef token when the
                    // member is defined in this same module, in which case, its TypeDef token can
                    // be used instead.)
                    Schema::TypeRef referenced_type(class_row);
                    auto resolution_scope_row = meta->read_row(referenced_type.ResolutionScope);
                    warnln("referenced type name: {}.{}", referenced_type.TypeNamespace, referenced_type.TypeName);
                    switch (referenced_type.ResolutionScope.table) {
                    case TableId::Module:
                    case TableId::ModuleRef:
                    case TableId::TypeRef:
                        TODO();
                        break;
                    case TableId::AssemblyRef: {
                        Schema::AssemblyRef referenced_assembly(resolution_scope_row);
                        warnln("loading referenced assembly: {}", referenced_assembly.Name);
                        //TODO: implement global assembly cache
                        String file_name;
                        if (referenced_assembly.Name == "System.Drawing")
                            file_name = "./System.Drawing.dll";
                        else
                            TODO();
                        auto assembly_reader = MUST(MetadataReader::create_from_file(file_name));

                        auto referenced_type_def = get_type(assembly_reader, referenced_type, referenced_assembly.Name, file_name);
                        Schema::TypeDef found_type_def = referenced_type_def.type;
                        Table type_table = referenced_type_def.table;
                        size_t type_index = referenced_type_def.index;

                        auto method_table = assembly_reader->find_table(TableId::MethodDef);
                        size_t method_search_upper_bound;
                        if (type_index == type_table.row_count - 1)
                            method_search_upper_bound = method_table.row_count;
                        else {
                            Schema::TypeDef next_type_def(assembly_reader->read_row(TableId::TypeDef, type_index + 1));
                            method_search_upper_bound = next_type_def.MethodList.index_plus_one;
                        }

                        MethodDef constructor_method;
                        bool found = false;
                        for (size_t i = found_type_def.MethodList.index_plus_one - 1; i < method_search_upper_bound; i++) {
                            Schema::MethodDef method_def(assembly_reader->read_row(TableId::MethodDef, i));
                            if (method_def.Name == constructor.Name) {
                                auto method_sig = TypeSignature::decode_method_signature(method_def.Signature);
                                if (method_sig == constructor_signature) {
                                    auto method = assembly_reader->make_method(method_def);
                                    if ((method.flags & (int)MethodAttributes::Static) != 0) {
                                        warnln("constructor is static.");
                                        VERIFY_NOT_REACHED();
                                    }
                                    constructor_method = method;
                                    found = true;
                                    break;
                                }
                            }
                        }
                        if (!found) {
                            warnln("Constructor method not found on type {}.{}", referenced_type.TypeNamespace, referenced_type.TypeName);
                            VERIFY_NOT_REACHED();
                        }

                        auto field_table = assembly_reader->find_table(TableId::Field);
                        size_t field_search_upper_bound;
                        if (type_index == type_table.row_count - 1)
                            field_search_upper_bound = field_table.row_count;
                        else {
                            Schema::TypeDef next_type_def(assembly_reader->read_row(TableId::TypeDef, type_index + 1));
                            field_search_upper_bound = next_type_def.FieldList.index_plus_one;
                        }

                        Vector<Schema::Field> fields;
                        for (size_t i = found_type_def.FieldList.index_plus_one - 1; i < field_search_upper_bound; i++) {
                            fields.append(Schema::Field { assembly_reader->read_row(TableId::Field, i) });
                        }
                        //TODO LEAK!!! Add GC
                        auto new_obj = m_heap.allocate<Object>(fields, String::formatted("{}.{}", referenced_type.TypeNamespace, referenced_type.TypeName));
                        auto args = pop_args(constructor_method.signature);
                        args.insert(0, new_obj);
                        eval(make_call(constructor_method, args, assembly_reader));
                        next();
                        break;
                    }
                    default:
                        VERIFY_NOT_REACHED();
                    }
                    break;
                }
                default:
                    VERIFY_NOT_REACHED();
                }
                break;
            }
            case InstructionCode::Ldarg_0:
            case InstructionCode::Ldarg_1:
            case InstructionCode::Ldarg_2:
            case InstructionCode::Ldarg_3: {
                size_t arg_index = (int)instruction.instruction_code - (int)InstructionCode::Ldarg_0;
                context.stack.append(context.arguments[arg_index]);
                next();
                break;
            }
            case InstructionCode::Ldarg_S:
            case InstructionCode::Ldarg: {
                size_t arg_index = instruction.instruction_operand.int_32_operand();
                context.stack.append(context.arguments[arg_index]);
                next();
                break;
            }
            case InstructionCode::Ldc_I4_0:
            case InstructionCode::Ldc_I4_1:
            case InstructionCode::Ldc_I4_2:
            case InstructionCode::Ldc_I4_3:
            case InstructionCode::Ldc_I4_4:
            case InstructionCode::Ldc_I4_5:
            case InstructionCode::Ldc_I4_6:
            case InstructionCode::Ldc_I4_7:
            case InstructionCode::Ldc_I4_8:
                context.stack.append((int)instruction.instruction_code - (int)InstructionCode::Ldc_I4_0);
                next();
                break;
            case InstructionCode::Stfld: {
                auto field_operand = instruction.instruction_operand.metadata_token();
                auto token = meta->resolve_token(field_operand);
                VERIFY(token.is_row());
                String field_name;
                if (token.row().table == TableId::MemberRef)
                    field_name = Schema::MemberRef(token.row().cells).Name;
                else if (token.row().table == TableId::Field)
                    field_name = Schema::Field(token.row().cells).Name;
                else
                    VERIFY_NOT_REACHED();
                auto value = pop_val();
                auto object_variant = pop_val();
                VERIFY(object_variant.has<Object*>());
                auto* object = object_variant.get<Object*>();
                object->set_field(field_name, value);
                next();
                break;
            }
            case InstructionCode::Ret:
                if (context.method.signature.return_type->type != TypeSignature::Type::PrimitiveTypeSig || context.method.signature.return_type->element_type != ElementType::Void) {
                    VERIFY(context.stack.size() == 1);
                    if (call_stack.size() > 1) {
                        auto& caller_context = call_stack[call_stack.size() - 2];
                        caller_context.stack.append(pop_val());
                    }
                }
                call_stack.take_last();
                return context;
            case InstructionCode::Brfalse:
            case InstructionCode::Brfalse_S:
                TODO();
                break;
            default:
                warnln("unimplemented instruction. operand type: {}", (int)instruction.instruction_operand.type());
                TODO();
            }
        }
        return context;
    }

    HashMap<String, Object*>& string_cache() { return m_string_cache; }
    void gather_roots(HashTable<Cell*>&);
    const StackInfo& stack_info() const { return m_stack_info; };

    CLIInterpreter()
        : m_mscorlib(MetadataReader::create_from_file("./mscorlib.dll").release_value())
        , m_heap(*this)
    {
        auto string_type_bundle = get_type_impl(m_mscorlib, "String", "System", "mscorlib", "./mscorlib.dll");
        auto type_index = string_type_bundle.index;
        auto type_table = string_type_bundle.table;
        auto found_type_def = string_type_bundle.type;
        // auto method_table = m_mscorlib->find_table(TableId::MethodDef);
        // size_t method_search_upper_bound;
        // if (type_index == type_table.row_count - 1)
        //     method_search_upper_bound = method_table.row_count;
        // else {
        //     Schema::TypeDef next_type_def(m_mscorlib->read_row(TableId::TypeDef, type_index + 1));
        //     method_search_upper_bound = next_type_def.MethodList.index_plus_one;
        // }

        // bool found = false;
        // for (size_t i = found_type_def.MethodList.index_plus_one - 1; i < method_search_upper_bound; i++) {
        //     Schema::MethodDef method_def(m_mscorlib->read_row(TableId::MethodDef, i));
        //     if (method_def.Name == ".ctor") {
        //         auto method_sig = TypeSignature::decode_method_signature(method_def.Signature);
        //         warnln("searching constructor {}", method_sig.dump(m_mscorlib));
        //         if (method_sig.params.size() == 1 && method_sig.params[0].type == TypeSignature::Type::RefTypeSig && method_sig.params[0].element_type == ElementType::Ptr && method_sig.params[0].type_signature->type == TypeSignature::Type::PrimitiveTypeSig && method_sig.params[0].type_signature->element_type == ElementType::Char) {
        //             auto method = m_mscorlib->make_method(method_def);
        //             if ((method.flags & (int)MethodAttributes::Static) != 0) {
        //                 warnln("constructor is static.");
        //                 VERIFY_NOT_REACHED();
        //             }
        //             m_string_constructor = method;
        //             found = true;
        //             break;
        //         }
        //     }
        // }
        // if (!found) {
        //     warnln("Constructor method not found on type System.String");
        //     VERIFY_NOT_REACHED();
        // }

        auto field_table = m_mscorlib->find_table(TableId::Field);
        size_t field_search_upper_bound;
        if (type_index == type_table.row_count - 1)
            field_search_upper_bound = field_table.row_count;
        else {
            Schema::TypeDef next_type_def(m_mscorlib->read_row(TableId::TypeDef, type_index + 1));
            field_search_upper_bound = next_type_def.FieldList.index_plus_one;
        }

        for (size_t i = found_type_def.FieldList.index_plus_one - 1; i < field_search_upper_bound; i++) {
            m_string_fields.append(Schema::Field { m_mscorlib->read_row(TableId::Field, i) });
        }
    }
};

ALWAYS_INLINE Heap& Cell::heap() const
{
    return HeapBlock::from_cell(this)->heap();
}
ALWAYS_INLINE CLIInterpreter& Cell::vm() const
{
    return heap().vm();
}
}
