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
