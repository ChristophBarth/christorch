cmake_minimum_required(VERSION 3.23)
project(christorch LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

# pybind11
FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG v2.12.0
)
FetchContent_MakeAvailable(pybind11)

# GoogleTest
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
)
FetchContent_MakeAvailable(googletest)

# Core library
add_library(christorch_core
    cpp/christorch/tensor/tensor.cpp
    cpp/christorch/ops/add.cpp
    cpp/christorch/autograd/engine.cpp
        cpp/include/core/dtype.h cpp/include/christorch/ops/add.h cpp/include/core/utils.h cpp/include/debug/nice_printing.h cpp/include/christorch/ops/matmul.h)
target_include_directories(christorch_core PUBLIC cpp/include)

# Python extension christorch._C
pybind11_add_module(_C
    cpp/bindings/module.cpp
    cpp/bindings/tensor_bindings.cpp
)
target_link_libraries(_C PRIVATE christorch_core)

# Install extension into python package dir for scikit-build
install(TARGETS _C LIBRARY DESTINATION python/christorch)

# ---------- Tests ----------
enable_testing()
add_executable(christorch_core_tests
    cpp/tests/test_tensor.cpp
        cpp/include/debug/nice_printing.h cpp/include/christorch/ops/matmul.h)
target_link_libraries(christorch_core_tests PRIVATE christorch_core gtest gtest_main)
add_test(NAME CoreTests COMMAND christorch_core_tests)

# ---------- Playground ----------
add_executable(playground cpp/playground.cpp cpp/include/core/utils.h cpp/include/debug/nice_printing.h cpp/include/christorch/ops/matmul.h)
target_link_libraries(playground PRIVATE christorch_core)