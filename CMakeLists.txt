cmake_minimum_required(VERSION 3.10)


project(Fossa)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

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

# Copy shaders folder.
# add_custom_command(TARGET Fossa POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
#                       ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:Fossa>/shaders)

set_property (TARGET ${PROJECT_NAME}
  PROPERTY
    # Enable C++17 standard compliance
    CXX_STANDARD 17
)

find_package(OpenGL REQUIRED)

# Add GLEW
add_definitions(-DGLEW_STATIC)
add_subdirectory(lib/glew)
target_link_libraries(Fossa libglew_static)

# Add GLFW
add_subdirectory(lib/glfw)
target_link_libraries(Fossa glfw)

# Add GLM
add_subdirectory(lib/glm)
target_link_libraries(Fossa glm)