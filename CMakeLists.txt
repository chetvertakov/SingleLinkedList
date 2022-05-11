cmake_minimum_required(VERSION 3.5)

project(SingleLinkedList LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (headers
    "singlelinkedlist.h")
add_executable(tests ${headers} test.cpp)

if(CMAKE_BUILD_TYPE MATCHES DEBUG)
if (MSVC)
    target_compile_options(SingleLinkedList PRIVATE /W4 /WX)
else ()
    target_compile_options(SingleLinkedList PRIVATE $<$<CONFIG:Debug>:
        -Werror
        -Wall
        -Wextra
        -Wpedantic
        -Wcast-align
        -Wcast-qual
        -Wconversion
        -Wctor-dtor-privacy
        -Wenum-compare
        -Wfloat-equal
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Woverloaded-virtual
        -Wredundant-decls
        -Wsign-conversion
        -Wsign-promo
        -pedantic
        -pedantic-errors
        >)
endif ()
endif ()
