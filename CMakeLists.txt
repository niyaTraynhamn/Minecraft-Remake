cmake_minimum_required(VERSION 3.16)
project(MinecraftGame LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Deps ----
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/External/glfw)

add_library(glad ${CMAKE_SOURCE_DIR}/External/glad/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/External/glad/include)

add_library(glm INTERFACE)
target_include_directories(glm INTERFACE ${CMAKE_SOURCE_DIR}/External)

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${CMAKE_SOURCE_DIR}/External/stb)

# ---- Your sources ----
add_executable(MinecraftGame
  # app
  ${CMAKE_SOURCE_DIR}/Src/main.cpp
  ${CMAKE_SOURCE_DIR}/Src/stb.cpp

  # engine: gl
  ${CMAKE_SOURCE_DIR}/Engine/Render/gl/shaderClass.cpp
  ${CMAKE_SOURCE_DIR}/Engine/Render/gl/textureClass.cpp
  ${CMAKE_SOURCE_DIR}/Engine/Render/gl/Vao.cpp
  ${CMAKE_SOURCE_DIR}/Engine/Render/gl/Vbo.cpp
  ${CMAKE_SOURCE_DIR}/Engine/Render/gl/Ebo.cpp

  # engine: render
  ${CMAKE_SOURCE_DIR}/Engine/Render/Mesh.cpp
  ${CMAKE_SOURCE_DIR}/Engine/Render/MeshHandle.cpp
  ${CMAKE_SOURCE_DIR}/Engine/Render/Renderer.cpp
  ${CMAKE_SOURCE_DIR}/Engine/Render/Material.cpp

  # engine: lighting
  #${CMAKE_SOURCE_DIR}/Engine/Render/lighting/Light.cpp

  # camera (adjust path to yours)
  ${CMAKE_SOURCE_DIR}/Engine/Render/camera.cpp

  # game
  ${CMAKE_SOURCE_DIR}/Game/Models/CubeMesh.cpp
)

# root include so you can do #include "Engine/..."
target_include_directories(MinecraftGame PUBLIC ${CMAKE_SOURCE_DIR})

target_link_libraries(MinecraftGame PRIVATE glad glfw glm stb)
if (WIN32)
  target_link_libraries(MinecraftGame PRIVATE opengl32)
endif()

add_custom_command(TARGET MinecraftGame POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_SOURCE_DIR}/Assets $<TARGET_FILE_DIR:MinecraftGame>/Assets
)

if (MSVC)
  target_compile_options(MinecraftGame PRIVATE /W4 /permissive-)
else()
  target_compile_options(MinecraftGame PRIVATE -Wall -Wextra -Wpedantic)
endif()

