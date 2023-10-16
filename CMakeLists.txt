cmake_minimum_required(VERSION 3.15)

project(fibonacci CXX)

find_package(fmt REQUIRED)
find_package(range-v3 REQUIRED)
find_package(cxxopts REQUIRED)
find_package(HighFive CONFIG REQUIRED)

# From https://github.com/microsoft/vcpkg/pull/34505/commits/ae9f98968edfe2147d54873321b79148f9bbd6d6

find_package(PkgConfig REQUIRED)
pkg_check_modules(matio REQUIRED IMPORTED_TARGET matio)

set(CMAKE_CXX_STANDARD 17)

add_executable(fibo main.cxx)

target_link_libraries(fibo
  PRIVATE
    fmt::fmt
    range-v3::range-v3
    cxxopts::cxxopts
    libdeps HighFive HighFive_libdeps HighFive_HighFive
    # Adapted from https://github.com/microsoft/vcpkg/pull/34505/commits/ae9f98968edfe2147d54873321b79148f9bbd6d6
    PkgConfig::matio
)

