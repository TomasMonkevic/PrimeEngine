cmake_minimum_required(VERSION 3.0.0)
project(PrimeIntegration VERSION 0.1.0)

#include(CTest)
#enable_testing()

set(PRIME_INTEGRATION_HEADERS
    "PrimeIntegration/Demo.h"
    "PrimeIntegration/FlappyBird.h"
    "PrimeIntegration/Game.h"
)

set(PRIME_INTEGRATION_SOURCES
    "PrimeIntegration/Demo.cpp"
    "PrimeIntegration/FlappyBird.cpp"
    "PrimeIntegration/Game.cpp"
    "PrimeIntegration/Main.cpp"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/PrimeEngine-Core)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/FreeType)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/GLFW/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/GLEW/include)

link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/PrimeEngine-Core
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/PrimeEngine-Core)

add_executable(PrimeIntegration ${PRIME_INTEGRATION_HEADERS} ${PRIME_INTEGRATION_SOURCES})
target_link_libraries(PrimeIntegration PrimeEngineCore)

add_dependencies(PrimeIntegration PrimeEngineCore)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)
