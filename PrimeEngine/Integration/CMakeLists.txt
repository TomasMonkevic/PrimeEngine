cmake_minimum_required(VERSION 3.0.0)
project(Integration VERSION 0.1.0)

#include(CTest)
#enable_testing()

set(PRIME_INTEGRATION_HEADERS
    "Demo.h"
    "FlappyBird.h"
    "Game.h"
)

set(PRIME_INTEGRATION_SOURCES
    "Demo.cpp"
    "FlappyBird.cpp"
    "Game.cpp"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Core)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/FreeType)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/GLFW/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/GLEW/include)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Core ${CMAKE_CURRENT_BINARY_DIR}/Core)

link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../Core
)

add_library(Integration SHARED ${PRIME_INTEGRATION_HEADERS} ${PRIME_INTEGRATION_SOURCES})
target_link_libraries(Integration PrimeEngineCore)

add_dependencies(Integration PrimeEngineCore)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)
