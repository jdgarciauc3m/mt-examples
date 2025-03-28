cmake_minimum_required(VERSION 3.30)
project(mt-exmples LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Weffc++ -Werror -pedantic -pedantic-errors -Wconversion -Wsign-conversion")
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -pedantic -pedantic-errors -Wconversion -Wsign-conversion")

add_subdirectory(c23)
add_subdirectory(cpp23)