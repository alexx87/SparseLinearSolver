cmake_minimum_required(VERSION 3.26.0)

SET(PROJECT_NAME "SparseLinearSolver")

project(${PROJECT_NAME})

set(MKL_ROOT "C:/Program Files (x86)/Intel/oneAPI/mkl/2023.0.0")
set(TEST_LANG CXX)
find_package(MKL CONFIG REQUIRED)

add_subdirectory(pardisoTestExample)
add_subdirectory(SparseLinearSolver)