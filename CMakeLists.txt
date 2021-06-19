cmake_minimum_required(VERSION 3.10)
project(opc)

find_package(LLVM REQUIRED CONFIG)
include_directories(.)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# For jsb: specific the address
include_directories(/usr/include/llvm-10)
include_directories(/usr/include/llvm-c-10)

execute_process(COMMAND llvm-config --libs OUTPUT_VARIABLE LLVM_LINK_LIBRARIES)
string(STRIP "${LLVM_LINK_LIBRARIES}" LLVM_LINK_LIBRARIES)

if(APPLE)
	include_directories(/usr/local/opt/llvm/include)
	string(APPEND CMAKE_CXX_FLAGS " -Wno-c++11-narrowing")
ENDIF(APPLE)


set(CMAKE_CXX_STANDARD 14)

aux_source_directory(ast AST_SOURCE)
aux_source_directory(generator GEN_SOURCE)
aux_source_directory(visitor VIS_SOURCE)

add_custom_command(
    OUTPUT lex.yy.cpp
    COMMAND lex -o lex.yy.cpp ${CMAKE_CURRENT_LIST_DIR}/lexer/pascal.l
    DEPENDS ${CMAKE_CURRENT_LIST_DIR}/lexer/pascal.l pascal.y.cpp
)

add_custom_command(
    OUTPUT y.tab.hpp y.tab.cpp 
    COMMAND yacc -d -o y.tab.cpp ${CMAKE_CURRENT_LIST_DIR}/parser/pascal.y
    DEPENDS ${CMAKE_CURRENT_LIST_DIR}/parser/pascal.y
)

# For jsb: "cannot find -lz", so must quote it
# llvm_map_components_to_libnames(LLVM_LINK_LIBRARIES core)

add_executable(
    opc
    main.cpp ${AST_SOURCE} ${GEN_SOURCE} ${VIS_SOURCE} lex.yy.cpp
    y.tab.cpp y.tab.hpp
        type/type.cpp)

set_target_properties(opc PROPERTIES LINK_LIBRARIES "${LLVM_LINK_LIBRARIES}")
