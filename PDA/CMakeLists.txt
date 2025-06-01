# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project Name
project(PDASystem CXX) # CXX indicates a C++ project

# Set C++ standard (C++11 required for range-based for, etc.)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the executable target and list its source files
add_executable(pda_app
    main.cpp
    PDA.cpp
    Task.cpp
    Note.cpp
    Storage.cpp
)

# Optional: Enable common compiler warnings for better code quality
if(MSVC)
    # Microsoft Visual C++ Compiler flags
    add_compile_options(/W4)
else()
    # GCC / Clang flags
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# Optional: Print a status message after configuration
message(STATUS "CMake configuration complete for pda_app. Use build tool (e.g., 'make') to compile.") 