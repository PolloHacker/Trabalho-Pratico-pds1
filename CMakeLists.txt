cmake_minimum_required(VERSION 3.10)  # Minimum required CMake version

project(TrabalhoPraticoPDS1)                   # Name your project

# Specify the C standard you want to use (optional)
set(CMAKE_C_STANDARD 11)

# Include header directory
include_directories(include)                # Include current directory for headers

# List your source files explicitly (recommended)
set(SOURCE_FILES src/main.c src/file_utils.c src/pok_utils.c)

# Create an executable
add_executable(TrabalhoPraticoPDS1 ${SOURCE_FILES})
