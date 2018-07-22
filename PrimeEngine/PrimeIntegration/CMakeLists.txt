cmake_minimum_required(VERSION 3.0.0)
project(PrimeIntegration VERSION 0.1.0)

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
    "Main.cpp"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../PrimeEngine-Core)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/FreeType)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/GLFW/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/GLEW/include)

link_directories(
    #${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/GLFW/build/src
    #${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/GLEW/build/cmake/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../PrimeEngine-Core
)

# add_definitions(-DGLEW_STATIC)
# add_definitions(-DBUILD_SHARED_LIBS)
# add_definitions(-fPIC)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../PrimeEngine-Core ${CMAKE_CURRENT_BINARY_DIR}/PrimeEngine-Core)
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/FreeType ${CMAKE_CURRENT_BINARY_DIR}/Dependencies/FreeType)
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/GLFW ${CMAKE_CURRENT_BINARY_DIR}/Dependencies/GLFW)
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/GLEW/build/cmake ${CMAKE_CURRENT_BINARY_DIR}/Dependencies/GLEW/build/cmake)

add_executable(PrimeIntegration ${PRIME_INTEGRATION_HEADERS} ${PRIME_INTEGRATION_SOURCES})
target_link_libraries(PrimeIntegration PrimeEngineCore)

add_dependencies(PrimeIntegration PrimeEngineCore)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)
