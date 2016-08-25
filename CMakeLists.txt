cmake_minimum_required(VERSION 3.0)
project(PyCall)

set(Python_ADDITIONAL_VERSIONS 3.4 3.5)


find_package( PythonLibs 3 REQUIRED )
add_executable(PyCall pycall.cpp)

include_directories(${PYTHON_INCLUDE_DIR})

# This has to be after the add_executable
target_link_libraries(PyCall ${PYTHON_LIBRARY})

