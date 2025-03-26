cmake_minimum_required(VERSION 3.28)
include(cmake/CPM.cmake)
project(Solstice)

# throw error if building for x86
if (CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(FATAL_ERROR "Solstice only supports x64 builds.")
endif ()

add_compile_definitions(__PRIVATE_DEBUG__)
add_compile_definitions(__PRIVATE_BUILD__)
add_compile_definitions(__DEBUG__)

find_program(LD_COMMAND ld)

if (NOT LD_COMMAND)
    find_program(LD_COMMAND ld HINTS "C:/msys64/mingw64/bin")
elseif (NOT LD_COMMAND)
    message(STATUS "ld found using find_program")
endif ()

execute_process(COMMAND ${LD_COMMAND} --version OUTPUT_VARIABLE LD_COMMAND_AVAILABLE)

message(STATUS "ld found at ${LD_COMMAND}")
if (NOT LD_COMMAND_AVAILABLE)
    message(FATAL_ERROR "The ld command is not available on your system. \nPlease install using `pacman -S mingw-w64-x86_64-binutils` in MSYS2, then add the bin directory to your PATH.\nAfter that, restart your IDE and CMake should be able to find the ld command.")
endif ()

set(CMAKE_UNITY_BUILD TRUE)

CPMAddPackage(
        NAME spdlog
        GITHUB_REPOSITORY gabime/spdlog
        VERSION 1.9.2
)

CPMAddPackage(
        NAME magic_enum
        GITHUB_REPOSITORY Neargye/magic_enum
        VERSION 0.9.5
)

CPMAddPackage(
        NAME glm
        GITHUB_REPOSITORY g-truc/glm
        GIT_TAG 1.0.1
)

CPMAddPackage(
        NAME nlohmann_json
        GITHUB_REPOSITORY nlohmann/json
        VERSION 3.11.3
)

CPMAddPackage(
        NAME DirectXTK
        GITHUB_REPOSITORY microsoft/DirectXTK
        GIT_TAG main
)

CPMAddPackage(
        NAME cryptopp-cmake
        GITHUB_REPOSITORY abdes/cryptopp-cmake
        GIT_TAG master
)

if(MSVC)
    add_compile_options(/bigobj)
endif()

set(SHADER_DIR ${CMAKE_CURRENT_LIST_DIR}/src/Utils/Shaders)
set(SHADER_BIN_DIR ${CMAKE_BINARY_DIR}/SolsticeShaders)
set(HLSL_FILES_VS ${SHADER_DIR}/BlockInstanceVS.hlsl)
set(HLSL_FILES_PS ${SHADER_DIR}/DefaultPS.hlsl)
list(LENGTH HLSL_FILES_VS HLSL_FILES_VS_COUNT)
list(LENGTH HLSL_FILES_PS HLSL_FILES_PS_COUNT)
math(EXPR HLSL_FILES_COUNT "${HLSL_FILES_VS_COUNT} + ${HLSL_FILES_PS_COUNT}")

add_custom_target(SolsticeShaders ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/SolsticeShaders COMMENT "Building ${HLSL_FILES_COUNT} shaders" VERBATIM)

foreach(FILE ${HLSL_FILES_VS})
    get_filename_component(FILE_WE ${FILE} NAME_WE)
    add_custom_command(TARGET SolsticeShaders
            COMMAND cmd /c fxc.exe /nologo /Evertex_main /T vs_5_0 /Zi /Fh ${SHADER_BIN_DIR}/${FILE_WE}.inc /Fd ${CMAKE_BINARY_DIR}/${FILE_WE}.pdb ${FILE} > nul
            DEPENDS ${FILE}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Building shader ${FILE}"
            VERBATIM
    )
endforeach(FILE)

foreach(FILE ${HLSL_FILES_PS})
    get_filename_component(FILE_WE ${FILE} NAME_WE)
    add_custom_command(TARGET SolsticeShaders
            COMMAND cmd /c fxc.exe /nologo /Epixel_main /T ps_5_0 /Zi /Fh ${SHADER_BIN_DIR}/${FILE_WE}.inc /Fd ${CMAKE_BINARY_DIR}/${FILE_WE}.pdb ${FILE} > nul
            DEPENDS ${FILE}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Building shader ${FILE}"
            VERBATIM
    )
endforeach(FILE)

include_directories(${SHADER_BIN_DIR})
find_package(OpenMP)

add_custom_target(generate_build_info
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_SOURCE_DIR}/GenerateBuildInfo.cmake
        COMMENT "Generating build info [${CMAKE_BINARY_DIR}/build_info.h]"
)

include_directories(${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 26)

add_compile_definitions(NOMINMAX)
add_compile_definitions(JM_XORSTR_DISABLE_AVX_INTRINSICS)

add_compile_definitions(ENTT_SPARSE_PAGE=2048)
add_compile_definitions(ENTT_PACKED_PAGE=128)

set(IS_DEBUG_BUILD CMAKE_BUILD_TYPE STREQUAL "Debug")

if (${IS_DEBUG_BUILD})
        add_compile_definitions(__DEBUG__)
endif ()

add_link_options($<$<CONFIG:Debug>:/INCREMENTAL>) # enable incremental linking
add_link_options($<$<CONFIG:Debug>:/DEBUG>) # enable debugging
add_compile_options($<$<CONFIG:Debug>:/Zi>)

add_link_options($<$<CONFIG:Release>:/Zi>) # generate pdb
add_link_options($<$<CONFIG:Release>:/INCREMENTAL:NO>) # disable incremental linking
add_link_options($<$<CONFIG:Release>:/LTCG>) # link-time code generation
add_link_options($<$<CONFIG:Release>:/DEBUG>) # enable debugging
add_compile_options($<$<CONFIG:Release>:/O2>) # optimize for speed
add_compile_options($<$<CONFIG:Release>:/Oi>) # enable intrinsic functions
add_compile_options($<$<CONFIG:Release>:/GL>) # enable link-time code generation
add_compile_options($<$<CONFIG:Release>:/Gy>) # separate functions for linker
add_compile_options($<$<CONFIG:Release>:/Gw>) # optimize global data
add_compile_options($<$<CONFIG:Release>:/Gm->) # disable minimal rebuild
add_compile_options($<$<CONFIG:Release>:/GF>) # enable string pooling
add_compile_options($<$<CONFIG:Release>:/fp:fast>) # optimize floating point
add_compile_options($<$<CONFIG:Release>:/GR->) # disable RTTI
add_compile_options($<$<CONFIG:Release>:/Gd>) # use __cdecl for all functions
add_compile_options($<$<CONFIG:Release>:/MT>) # use static multithreaded runtime
add_compile_options($<$<CONFIG:Release>:/Ob2>) # inline any suitable function
add_compile_options($<$<CONFIG:Release>:/Ot>) # favor fast code
add_compile_options($<$<CONFIG:Release>:/Oy->) # omit frame pointers





set(SOLSTICE_VERSION "v1.0.0")
add_compile_definitions(SOLSTICE_VERSION="${SOLSTICE_VERSION}")

add_definitions(-DWIN32_LEAN_AND_MEAN)

include_directories(.)
include_directories(src)
include_directories(include)
include_directories(include/minhook/include)
include_directories(include/libhat)
include_directories(include/entt)
include_directories(include/libhat/libhat)
include_directories(include/ImGui)
include_directories(include/Kiero)
include_directories(include/nes)
include_directories(include/Modules)
include_directories(src/Features) # Добавил путь к модулям, если у вас есть папка Modules с файлами, такими как Module.hpp

file(GLOB_RECURSE sourceFiles "src/*.cpp")
file(GLOB_RECURSE includeFiles "include/*.hpp")
set_source_files_properties(${sourceFiles} PROPERTIES CXX_SCAN_FOR_MODULES OFF)
set_source_files_properties(${includeFiles} PROPERTIES CXX_SCAN_FOR_MODULES OFF)


# Krazy resource embedding code

file(GLOB_RECURSE resource_files_list "resources/*")

function(add_resources out_var)
    set(result)
    foreach(in_f ${ARGN})
        file(RELATIVE_PATH src_f ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${in_f})
        set(out_f "${PROJECT_BINARY_DIR}/${in_f}.o")
        add_custom_command(OUTPUT ${out_f}
                COMMAND ${LD_COMMAND} -r -b binary -o ${out_f} ${src_f}
                DEPENDS ${in_f}
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                COMMENT "Building object ${out_f}"
                VERBATIM
        )
        list(APPEND result ${out_f})
        message(STATUS "Embedding resource: ${in_f}")
    endforeach()
    set(${out_var} "${result}" PARENT_SCOPE)
endfunction()


set(resource_files ""
        src/Features/Modules/Render/Counters.cpp
        src/Features/Modules/Render/PlayerList.cpp
        src/Features/Modules/Render/HitEffects.cpp
        src/Features/Modules/Render/HPBar.cpp
        src/Features/Modules/Combat/AutoPot.cpp
        src/Features/Modules/Combat/AimAssist.cpp
        src/Features/Modules/Render/TargetHUD.cpp
        src/Features/Modules/Other/MCF.cpp
        src/Features/Modules/Other/MCP.cpp
        src/Features/Modules/Other/Breaker.cpp
        src/Features/Modules/Render/Ambience.cpp
        src/Features/Modules/Render/Keystrokes.cpp
        src/Features/Modules/Render/Keystrokes.hpp
        src/Features/Modules/Other/AutoHive.cpp
        src/Features/Modules/Other/AutoHive.hpp
        src/Features/Modules/Render/BabyBoy.cpp
        src/Features/Modules/Render/BabyBoy.hpp)
foreach(file ${resource_files_list})
    file(RELATIVE_PATH relative_file ${CMAKE_CURRENT_SOURCE_DIR}/resources ${file})
    list(APPEND resource_files resources/${relative_file})
endforeach()

add_resources(resource_files ${resource_files})

add_library(Solstice SHARED ${sourceFiles} ${resource_files}
        src/Features/Modules/Render/Counters.cpp
        src/Features/Modules/Render/TargetHUD.cpp
        src/Features/Modules/Other/MCF.cpp
        src/Features/Modules/Other/MCP.cpp
        src/Features/Modules/Other/Breaker.cpp
        src/Features/Modules/Render/Ambience.cpp
        src/Features/Modules/Render/Keystrokes.cpp
        src/Features/Modules/Render/Keystrokes.hpp
        src/Features/Modules/Other/AutoHive.cpp
        src/Features/Modules/Other/AutoHive.hpp
        src/Features/Modules/Render/BabyBoy.cpp
        src/Features/Modules/Render/BabyBoy.hpp)
add_dependencies(${PROJECT_NAME} generate_build_info SolsticeShaders)

set(RESOURCE_HEADER_FILE "${CMAKE_CURRENT_SOURCE_DIR}/src/Utils/Resources.hpp")
set(RESOURCE_SOURCE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/src/Utils/Resources.cpp")


set(RESOURCE_HEADER_CONTENT "// This file is generated by CMake. Do not edit it manually.\n")
set(RESOURCE_HEADER_CONTENT "${RESOURCE_HEADER_CONTENT}#pragma once\n")
set(RESOURCE_HEADER_CONTENT "${RESOURCE_HEADER_CONTENT}#include <string>\n")
set(RESOURCE_HEADER_CONTENT "${RESOURCE_HEADER_CONTENT}#include <unordered_map>\n")
set(RESOURCE_HEADER_CONTENT "${RESOURCE_HEADER_CONTENT}#include \"Resource.hpp\"\n")
set(RESOURCE_HEADER_CONTENT "${RESOURCE_HEADER_CONTENT}\n")

foreach(file ${resource_files_list})
    file(RELATIVE_PATH relative_file ${CMAKE_CURRENT_SOURCE_DIR}/resources ${file})
    string(REPLACE "/" "_" resource_name ${relative_file})
    string(REPLACE "." "_" resource_name ${resource_name})
    string(REPLACE "-" "_" resource_name ${resource_name})
    set(RESOURCE_HEADER_CONTENT "${RESOURCE_HEADER_CONTENT}extern const Resource ${resource_name};\n")
endforeach()

file(WRITE ${RESOURCE_HEADER_FILE} ${RESOURCE_HEADER_CONTENT})

message(STATUS "Writing resource header file to ${RESOURCE_HEADER_FILE}")

add_dependencies(${PROJECT_NAME} generate_build_info SolsticeShaders)

set(CMAKE_CXX_STANDARD 26)
