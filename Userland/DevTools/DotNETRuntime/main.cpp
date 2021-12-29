/*
 * Copyright (c) 2021, Daniel Flaws <dflaws1@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#pragma GCC optimize("O0")

#include "CLIInterpreter.h"
#include <LibCore/ArgsParser.h>
#include <LibMain/Main.h>

ErrorOr<int> serenity_main(Main::Arguments arguments)
{
    DotNETRuntime::CodedIndex::init_coded_indexes();
    DotNETRuntime::SchemaUtils::init_schema();
    Core::ArgsParser args;

    String file_name;
    args.add_positional_argument(file_name, "The .NET file to run", "fileName");
    args.parse(arguments);

    warnln("Loading mscorlib...");
    DotNETRuntime::CLIInterpreter interpreter;

    auto reader = TRY(DotNETRuntime::MetadataReader::create_from_file(file_name));
    auto entry_point = reader->read_entry_point();

    auto context = interpreter.make_call(entry_point, {}, reader);
    interpreter.eval(context);

    return 0;
}
