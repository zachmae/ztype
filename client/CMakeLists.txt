cmake_minimum_required(VERSION 3.17)
project(client)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 20)
set(GRAPHICS GRAPHICS_API_OPENGL_43)
set(OpenGL_GL_PREFERENCE GLVND)

include(FindSfmlLib.cmake)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-Wall -Wextra -Wconversion)
endif(CMAKE_COMPILER_IS_GNUCXX)

if (WIN32)
    add_compile_options(-Wall)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "./")
endif(WIN32)

#ADD_LIBRARY(MyStaticLib STATIC
add_executable(${PROJECT_NAME}
        src/main.cpp
        src/client.cpp
        )

include_directories(includes/)

target_link_libraries(${PROJECT_NAME}
        sfml-network
)
