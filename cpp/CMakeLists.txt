cmake_minimum_required(VERSION 3.18)

project(rosbags_cpp VERSION 0.1.0 LANGUAGES CXX)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development.Embed)
find_package(pybind11 CONFIG REQUIRED)

add_library(rosbags_cpp src/rosbags.cpp)
add_library(rosbags_cpp::rosbags_cpp ALIAS rosbags_cpp)

target_compile_features(rosbags_cpp PUBLIC cxx_std_17)
target_include_directories(
  rosbags_cpp
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(rosbags_cpp PRIVATE pybind11::embed Python3::Python)

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
endif()

option(ROSBAGS_CPP_BUILD_TESTS "Build rosbags C++ integration tests" OFF)
set(ROSBAGS_CPP_PYTHONPATH "" CACHE PATH "Path to a rosbags Python source checkout for tests")
if(ROSBAGS_CPP_BUILD_TESTS)
  include(CTest)
  add_executable(rosbags_cpp_api_test tests/cpp_api_test.cpp)
  target_link_libraries(rosbags_cpp_api_test PRIVATE rosbags_cpp::rosbags_cpp)
  add_test(
    NAME rosbags_cpp_api_test
    COMMAND
      rosbags_cpp_api_test
      "${ROSBAGS_CPP_PYTHONPATH}"
      "${CMAKE_CURRENT_BINARY_DIR}/rosbags_cpp_api_tmp"
  )
  if(WIN32)
    set(_rosbags_cpp_pythonpath_sep ";")
  else()
    set(_rosbags_cpp_pythonpath_sep ":")
  endif()
  set(_rosbags_cpp_test_pythonpath "${ROSBAGS_CPP_PYTHONPATH}")
  if(Python3_SITELIB)
    set(
      _rosbags_cpp_test_pythonpath
      "${_rosbags_cpp_test_pythonpath}${_rosbags_cpp_pythonpath_sep}${Python3_SITELIB}"
    )
  endif()
  if(Python3_SITEARCH AND NOT Python3_SITEARCH STREQUAL Python3_SITELIB)
    set(
      _rosbags_cpp_test_pythonpath
      "${_rosbags_cpp_test_pythonpath}${_rosbags_cpp_pythonpath_sep}${Python3_SITEARCH}"
    )
  endif()
  set_tests_properties(
    rosbags_cpp_api_test
    PROPERTIES ENVIRONMENT "PYTHONPATH=${_rosbags_cpp_test_pythonpath}"
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
