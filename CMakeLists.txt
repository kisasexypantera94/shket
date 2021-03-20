cmake_minimum_required(VERSION 3.15)
project(shket)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_COMPILER /usr/local/opt/llvm/bin/clang++)
#set(CMAKE_C_COMPILER /usr/local/opt/llvm/bin/clang)
set(CMAKE_CXX_COMPILER /usr/local/opt/gcc/bin/g++-10)
set(CMAKE_C_COMPILER /usr/local/opt/gcc/bin/gcc-10)

add_library(
        indexer

        src/tokenizer.cpp
        src/utils.cpp
        src/index.cpp)

target_include_directories(
        indexer
        SYSTEM
        PUBLIC


        /usr/local/opt/gcc/include
        #        /usr/local/opt/icu4c/include

        include
        thirdparty
)

target_link_directories(
        indexer
        PRIVATE

        /usr/local/opt/gcc/lib
        #        /usr/local/lib
        #        /usr/local/opt/icu4c/lib
)

target_link_libraries(
        indexer

        #        icuio
        #        icuuc
)

target_compile_options(
        indexer
        PRIVATE

        -m64

        -ffast-math
        -Ofast
        -march=native

        -pedantic
        -Wall
        -Wextra
        -Wcast-align
        -Wcast-qual
        -Wctor-dtor-privacy
        -Wformat=2
        -Winit-self
#        -Wmissing-declarations
        -Wmissing-include-dirs
        -Woverloaded-virtual
        -Wredundant-decls
        -Wsign-promo
        -Wstrict-overflow=5
        -Wswitch-default
        -Wundef
        -Wno-unused
)

add_subdirectory(bin)
