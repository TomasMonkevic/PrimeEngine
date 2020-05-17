cmake_minimum_required(VERSION 3.0.0)
project(LinuxIntegration VERSION 0.1.0)

#include(CTest)
#enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../Integration)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../Core)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../Dependencies/FreeType)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../Dependencies/GLFW/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../Dependencies/GLEW/include)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../Integration ${CMAKE_CURRENT_BINARY_DIR}/Integration)

link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Integration
)

add_executable(LinuxIntegration "Main.cpp")
target_link_libraries(LinuxIntegration Integration)

add_dependencies(LinuxIntegration Integration)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)
