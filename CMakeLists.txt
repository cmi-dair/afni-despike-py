cmake_minimum_required(VERSION 3.15...3.26)
project(${SKBUILD_PROJECT_NAME} LANGUAGES C)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_C_FLAGS "-pedantic -Wall -Wextra -Wno-unused-parameter -Wno-incompatible-pointer-types")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O3")

# Grab the variables from a local Python installation
# NumPy headers
execute_process(
  COMMAND "${PYTHON_EXECUTABLE}"
  -c "import numpy; print(numpy.get_include())"
  OUTPUT_VARIABLE NumPy_INCLUDE_DIRS
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

find_package(Python COMPONENTS Interpreter Development.Module REQUIRED)

FILE(GLOB MyCSources ./src/*.c)
python_add_library(${SKBUILD_PROJECT_NAME} MODULE ${MyCSources} WITH_SOABI)

target_include_directories(${SKBUILD_PROJECT_NAME} PUBLIC
                           ${NumPy_INCLUDE_DIRS}
                           ${PYTHON_INCLUDE_DIRS})


install(TARGETS ${SKBUILD_PROJECT_NAME} DESTINATION .)