cmake_minimum_required(VERSION 3.14)
project(PROC1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Generate compile_commands.json for IDE/tooling support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Main executable — header-only project, only main.cpp needs compilation
add_executable(main main.cpp)

# Include path: project root so #include "Common/Utils.h" works
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR})

# Warnings
target_compile_options(main PRIVATE -Wall -Wextra)

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
target_compile_options(test_pokemon_logic PRIVATE -Wall -Wextra)
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
