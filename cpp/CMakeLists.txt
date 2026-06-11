# Copyright 2020-2026 Ternaris
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.18)

project(rosbags_cpp VERSION 0.2.0 LANGUAGES CXX)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

find_package(SQLite3 REQUIRED)
find_package(OpenSSL REQUIRED COMPONENTS Crypto)
find_package(BZip2 REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(YAML_CPP REQUIRED yaml-cpp)
pkg_check_modules(LZ4 REQUIRED liblz4)
pkg_check_modules(ZSTD REQUIRED libzstd)

add_library(rosbags_cpp src/rosbags.cpp)
add_library(rosbags_cpp::rosbags_cpp ALIAS rosbags_cpp)

target_compile_features(rosbags_cpp PUBLIC cxx_std_17)
target_include_directories(
  rosbags_cpp
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE
    ${YAML_CPP_INCLUDE_DIRS}
    ${LZ4_INCLUDE_DIRS}
    ${ZSTD_INCLUDE_DIRS}
)
target_link_libraries(
  rosbags_cpp
  PRIVATE
    SQLite::SQLite3
    OpenSSL::Crypto
    BZip2::BZip2
    ${YAML_CPP_LINK_LIBRARIES}
    ${LZ4_LINK_LIBRARIES}
    ${ZSTD_LINK_LIBRARIES}
)
target_link_directories(
  rosbags_cpp
  PRIVATE
    ${YAML_CPP_LIBRARY_DIRS}
    ${LZ4_LIBRARY_DIRS}
    ${ZSTD_LIBRARY_DIRS}
)
target_compile_options(
  rosbags_cpp
  PRIVATE
    ${YAML_CPP_CFLAGS_OTHER}
    ${LZ4_CFLAGS_OTHER}
    ${ZSTD_CFLAGS_OTHER}
)

set_target_properties(
  rosbags_cpp
  PROPERTIES
    EXPORT_NAME rosbags_cpp
)

option(ROSBAGS_CPP_BUILD_EXAMPLES "Build rosbags C++ examples" OFF)
if(ROSBAGS_CPP_BUILD_EXAMPLES)
  add_executable(rosbags_cpp_read_raw examples/read_raw.cpp)
  target_link_libraries(rosbags_cpp_read_raw PRIVATE rosbags_cpp::rosbags_cpp)

  add_executable(rosbags_cpp_copy_raw examples/copy_raw.cpp)
  target_link_libraries(rosbags_cpp_copy_raw PRIVATE rosbags_cpp::rosbags_cpp)

  add_executable(rosbags_cpp_bench_raw examples/bench_raw.cpp)
  target_link_libraries(rosbags_cpp_bench_raw PRIVATE rosbags_cpp::rosbags_cpp)

  add_executable(rosbags_cpp_convert examples/convert.cpp)
  target_link_libraries(rosbags_cpp_convert PRIVATE rosbags_cpp::rosbags_cpp)
endif()

option(ROSBAGS_CPP_BUILD_TESTS "Build rosbags C++ integration tests" OFF)
if(ROSBAGS_CPP_BUILD_TESTS)
  include(CTest)
  add_executable(rosbags_cpp_api_test tests/cpp_api_test.cpp)
  target_link_libraries(rosbags_cpp_api_test PRIVATE rosbags_cpp::rosbags_cpp)
  add_test(
    NAME rosbags_cpp_api_test
    COMMAND
      rosbags_cpp_api_test
      "${CMAKE_CURRENT_BINARY_DIR}/rosbags_cpp_api_tmp"
  )
endif()

install(
  TARGETS rosbags_cpp
  EXPORT rosbags_cppTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

configure_package_config_file(
  cmake/rosbags_cppConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/rosbags_cppConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/rosbags_cpp
)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/rosbags_cppConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)
install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/rosbags_cppConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/rosbags_cppConfigVersion.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/rosbags_cpp
)
install(
  EXPORT rosbags_cppTargets
  NAMESPACE rosbags_cpp::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/rosbags_cpp
)
