cmake_minimum_required(VERSION 3.14)
project(PROC1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Generate compile_commands.json for IDE/tooling support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Windows architecture — ensure proper target architecture is defined
if(WIN32)
    # Define _AMD64_ for 64-bit builds or _X86_ for 32-bit builds
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        add_definitions(-D_AMD64_)
    else()
        add_definitions(-D_X86_)
    endif()
endif()

# Main executable — header-only project, only main.cpp needs compilation
add_executable(main main.cpp)

# Include path: project root so #include "Common/Utils.h" works
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR})

# Warnings — platform-specific flags
if(MSVC)
    target_compile_options(main PRIVATE /W4)
else()
    target_compile_options(main PRIVATE -Wall -Wextra)
endif()

# Platform-specific linking
if(WIN32)
    target_link_libraries(main PRIVATE winmm)
else()
    find_package(Threads REQUIRED)
    target_link_libraries(main PRIVATE Threads::Threads)
endif()

# --- Testing ---
enable_testing()

# PokemonLogicTest — validates Pokemon logic (RunCommand, Move defaults, null safety, etc.)
add_executable(test_pokemon_logic Tests/PokemonLogicTest.cpp)
target_include_directories(test_pokemon_logic PRIVATE ${CMAKE_SOURCE_DIR})
if(MSVC)
    target_compile_options(test_pokemon_logic PRIVATE /W4)
else()
    target_compile_options(test_pokemon_logic PRIVATE -Wall -Wextra)
endif()
if(WIN32)
    target_link_libraries(test_pokemon_logic PRIVATE winmm)
else()
    find_package(Threads REQUIRED)
    target_link_libraries(test_pokemon_logic PRIVATE Threads::Threads)
endif()
add_test(NAME PokemonLogic COMMAND test_pokemon_logic)

# --- Formatting ---
# Find clang-format and define a 'format' target that reformats all project sources
find_program(CLANG_FORMAT_EXECUTABLE clang-format)
if(CLANG_FORMAT_EXECUTABLE)
    file(GLOB_RECURSE ALL_SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/Common/*.h
        ${CMAKE_SOURCE_DIR}/Juegos/*.h
        ${CMAKE_SOURCE_DIR}/Juegos/*.cpp
        ${CMAKE_SOURCE_DIR}/MainMenu/*.h
        ${CMAKE_SOURCE_DIR}/MainMenu/*.cpp
        ${CMAKE_SOURCE_DIR}/Tests/*.cpp
        ${CMAKE_SOURCE_DIR}/Tests/*.h
        ${CMAKE_SOURCE_DIR}/*.cpp
    )
    add_custom_target(format
        COMMAND ${CLANG_FORMAT_EXECUTABLE} -i ${ALL_SOURCE_FILES}
        COMMENT "Formatting all project sources with clang-format"
        VERBATIM
    )
else()
    message(WARNING "clang-format not found — 'format' target will not be available")
endif()
