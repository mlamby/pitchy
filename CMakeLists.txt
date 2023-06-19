cmake_minimum_required(VERSION 3.16)

project(pitchy CXX)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_23)

# Link this project_warnings 'library' to use the warnings specified in 
# CompilerWarnings.cmake
add_library(project_warnings INTERFACE)
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# Dependencies managed via vcpkg
find_package(rtmidi CONFIG REQUIRED)
find_package(argh CONFIG REQUIRED)

include(CTest)

add_subdirectory(src)

if(BUILD_TESTING)
  find_package(Catch2 CONFIG REQUIRED)
  add_subdirectory(test)
endif()