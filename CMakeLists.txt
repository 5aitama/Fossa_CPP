cmake_minimum_required(VERSION 3.10)

project(Fossa)

file(GLOB_RECURSE Fossa_SOURCES "src/*.cpp")
file(GLOB_RECURSE Fossa_HEADERS "src/*.hpp")

if(UNIX AND NOT APPLE)
        set(OpenGL_GL_PREFERENCE LEGACY)
endif()

find_package(OpenGL REQUIRED)

# Don't build glfw docs, test and exemples...
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_executable(Fossa ${Fossa_SOURCES} ${Fossa_HEADERS})

find_package(OpenGL REQUIRED)

# Add GLEW
add_definitions(-DGLEW_STATIC)
add_subdirectory(lib/glew EXCLUDE_FROM_ALL)
target_link_libraries(Fossa PRIVATE libglew_static)

# Add GLFW
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
target_link_libraries(Fossa PRIVATE glfw)

# Add GLM
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
target_link_libraries(Fossa PRIVATE glm)