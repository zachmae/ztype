cmake_minimum_required(VERSION 3.17)
project(rtype)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 20)
set(GRAPHICS GRAPHICS_API_OPENGL_43)
set(OpenGL_GL_PREFERENCE GLVND)

include(cmake/FindJsonLib.cmake)
include(cmake/FindSfmlLib.cmake)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-Wall -Wextra -Wconversion)
endif(CMAKE_COMPILER_IS_GNUCXX)

if (WIN32)
    add_compile_options(-Wall)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "./")
    #set_target_properties (rtype.exe PROPERTIES PREFIX "./build/")
endif(WIN32)

#ADD_LIBRARY(MyStaticLib STATIC
add_executable(${PROJECT_NAME}
        src/main.cpp
        src/Network/Server.cpp
        src/Network/Client.cpp
        src/ECS/Systems/AnimationSystem.cpp
        src/ECS/Systems/PositionSystem.cpp
        src/ECS/Systems/DisplaySystem.cpp
        src/ECS/Systems/EventSystem.cpp
        )

include_directories(includes)

target_link_libraries(${PROJECT_NAME}
    sfml-window
    sfml-graphics
    sfml-network
    sfml-audio
    nlohmann_json::nlohmann_json
)

install(TARGETS rtype RUNTIME DESTINATION bin)
include(CPack)