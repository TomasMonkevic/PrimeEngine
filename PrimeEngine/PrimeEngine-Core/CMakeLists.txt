cmake_minimum_required(VERSION 3.0.0)
project(PrimeEngineCore VERSION 0.1.0)

#include(CTest)
#enable_testing()

set(PECORE_HEADERS
    "Components/Behaviour.h"
    "Components/Behaviours/FpsCamera.h"
    "Components/Component.h"
    "Components/Object.h"
    "Components/Transform.h"
    "DllExport.h"
    "GameObject.h"
    "Graphics/BatchRenderer2D.h"
    "Graphics/Buffers/IndexBuffer.h"
    "Graphics/Buffers/VertexArray.h"
    "Graphics/Buffers/VertexBuffer.h"
    "Graphics/Camera.h"
    "Graphics/Color.h"
    "Graphics/Font.h"
    "Graphics/Label.h"
    "Graphics/Layers/GameLayer.h"
    "Graphics/Layers/Layer.h"
    "Graphics/Layers/UILayer.h"
    "Graphics/Lights/AmbientLight.h"
    "Graphics/Lights/DirectionalLight.h"
    "Graphics/Lights/Light.h"
    "Graphics/Lights/PointLight.h"
    "Graphics/Lights/SpotLight.h"
    "Graphics/Material.h"
    "Graphics/Mesh.h"
    "Graphics/MeshRenderer.h"
    "Graphics/ModelImporter.h"
    "Graphics/Renderable.h"
    "Graphics/Renderer2D.h"
    "Graphics/Shader/Shader.h"
    "Graphics/Shader/ShaderManager.h"
    "Graphics/Sprite.h"
    "Graphics/stb_image.h"
    "Graphics/Texture.h"
    "Math/Quaternion.h"
    "PrimeEngine.h"
    "Scene.h"
    "UI/Text.h"
    "UI/UIObject.h"
    "Input.h"
    "Math/Math.h"
    "Math/MathFunc.h"
    "Math/Matrix4x4.h"
    "Math/Vector2.h"
    "Math/Vector4.h"
    "Graphics/Window.h"
    "Math/Vector3.h"
    #"Networking/TCPClient.h" TODO add later
    #"Networking/NetworkEntity.h"
    #"Networking/TCPServer.h"
    "PrimeEngineBase.h"
    "PrimeException.h"
    "Utilities/File.h"
    "Utilities/Log.h"
    "Utilities/Time.h"
    "Utilities/Utils.h"
)

set(PECORE_SOURCES
    "Components/Behaviour.cpp"
    "Components/Behaviours/FpsCamera.cpp"
    "Components/Transform.cpp"
    "GameObject.cpp"
    "Graphics/BatchRenderer2D.cpp"
    "Graphics/Buffers/IndexBuffer.cpp"
    "Graphics/Buffers/VertexArray.cpp"
    "Graphics/Buffers/VertexBuffer.cpp"
    "Graphics/Camera.cpp"
    "Graphics/Color.cpp"
    "Graphics/Font.cpp"
    "Graphics/Label.cpp"
    "Graphics/Layers/GameLayer.cpp"
    "Graphics/Layers/Layer.cpp"
    "Graphics/Layers/UILayer.cpp"
    "Graphics/Lights/AmbientLight.cpp"
    "Graphics/Lights/DirectionalLight.cpp"
    "Graphics/Lights/PointLight.cpp"
    "Graphics/Lights/SpotLight.cpp"
    "Graphics/Material.cpp"
    "Graphics/Mesh.cpp"
    "Graphics/MeshRenderer.cpp"
    "Graphics/ModelImporter.cpp"
    "Graphics/Shader/Shader.cpp"
    "Graphics/Shader/ShaderManager.cpp"
    "Graphics/Sprite.cpp"
    "Graphics/Texture.cpp"
    "Input.cpp"
    "Math/Matrix4x4.cpp"
    "Math/Quaternion.cpp"
    "Math/Vector2.cpp"
    "Math/Vector4.cpp"
    "Graphics/Window.cpp"
    "Math/Vector3.cpp"
    #"Networking/TCPClient.cpp" TODO add later
    #"Networking/TCPSever.cpp"
    "PrimeEngineBase.cpp"
    "PrimeException.cpp"
    "Scene.cpp"
    "UI/Text.cpp"
    "Utilities/Time.cpp"
    "Utilities/Utils.cpp"
)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/FreeType)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/GLFW/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/GLEW/include)

link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/GLEW/build/cmake/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/GLFW/build/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/FreeType/build)

add_definitions(-DGLEW_STATIC)
#add_definitions(-DBUILD_SHARED_LIBS)
add_definitions(-fPIC)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/GLFW ${CMAKE_CURRENT_BINARY_DIR}/Dependencies/GLFW)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/GLEW/build/cmake ${CMAKE_CURRENT_BINARY_DIR}/Dependencies/GLEW/build/cmake)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/FreeType ${CMAKE_CURRENT_BINARY_DIR}/Dependencies/FreeType)

add_library(PrimeEngineCore SHARED ${PECORE_HEADERS} ${PECORE_SOURCES})

target_link_libraries(PrimeEngineCore
    glew_s
    glfw
    FreeType
)

add_dependencies(PrimeEngineCore glew_s glfw FreeType)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)
