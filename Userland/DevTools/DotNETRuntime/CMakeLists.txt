serenity_component(
    DotNETRuntime
    RECOMMENDED
    TARGETS DotNETRuntime
)

set(SOURCES
    CLIInterpreter.cpp
    CodedIndex.cpp
    Heap/BlockAllocator.cpp
    Heap/CellAllocator.cpp
    Heap/Handle.cpp
    Heap/Heap.cpp
    Heap/HeapBlock.cpp
    Heap/MarkedVector.cpp
    MetadataReader.cpp
    MethodDef.cpp
    MethodSignature.cpp
    Object.cpp
    Schema.cpp
    Signature.cpp
    TableIndex.cpp
    Variant.cpp
    main.cpp
)

serenity_app(DotNETRuntime ICON app-dot-net-runtime)
target_link_libraries(DotNETRuntime LibMain LibCore)