cmake_minimum_required(VERSION 3.15)
project(Learn-OpenGL)
set(CMAKE_CXX_STANDARD 17)

# OpenGL
find_package(OpenGL REQUIRED)

# GLAD
include_directories(externals/glad/include)

# GLFW
# GLFW의 docs, tests, examples를 빌드하지 않는 옵션
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(externals/glfw)
include_directories(externals/glfw)

# GLM
add_subdirectory(externals/glm)
include_directories(externals/glm)

# ASSIMP
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(externals/assimp)
include_directories(externals/assimp)

# Project execute
add_executable(${PROJECT_NAME}
        externals/glad/src/glad.c

        # src/1.Getting-Started/1.1.Hello-Window.cpp
        # src/1.Getting-Started/1.2.Hello-Triangle.cpp
        # src/1.Getting-Started/1.3.Shaders.cpp
        # src/1.Getting-Started/1.4.Textures.cpp
        # src/1.Getting-Started/1.5.Transformations.cpp
        # src/1.Getting-Started/1.6.Coordinate-Systems.cpp
        # src/1.Getting-Started/1.7.Camera.cpp
        # src/2.Lighting/2.1.Colors.cpp
        # src/2.Lighting/2.2.Basic-Lighting.cpp
        # src/2.Lighting/2.3.Materials.cpp
        # src/2.Lighting/2.4.Lighting-maps.cpp
        # src/2.Lighting/2.5.Light-casters.cpp
        # src/2.Lighting/2.6.Multiple-lights.cpp
        src/3.Model-Loading/3.1.Model-loading.cpp
)
target_link_libraries(${PROJECT_NAME}
        OpenGL::GL
        glfw
        assimp
)
