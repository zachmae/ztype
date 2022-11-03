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
    add_compile_options(/W4)
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

include_directories(includes
                    modules)

target_link_libraries(${PROJECT_NAME}
    sfml-window
    sfml-graphics
    sfml-network
    sfml-audio
    sfml-system
)

if (WIN32)
  add_custom_command(TARGET rtype POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${FETCHCONTENT_BASE_DIR}/sfml-build/lib/Debug/sfml-window-d-2.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}
    COMMAND_EXPAND_LISTS
  )
  add_custom_command(TARGET rtype POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${FETCHCONTENT_BASE_DIR}/sfml-build/lib/Debug/sfml-network-d-2.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}
    COMMAND_EXPAND_LISTS
  )
  add_custom_command(TARGET rtype POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${FETCHCONTENT_BASE_DIR}/sfml-build/lib/Debug/sfml-system-d-2.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}
    COMMAND_EXPAND_LISTS
  )
  add_custom_command(TARGET rtype POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${FETCHCONTENT_BASE_DIR}/sfml-build/lib/Debug/sfml-graphics-d-2.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}
    COMMAND_EXPAND_LISTS
  )
  add_custom_command(TARGET rtype POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${FETCHCONTENT_BASE_DIR}/sfml-build/lib/Debug/sfml-audio-d-2.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}
    COMMAND_EXPAND_LISTS
  )
  add_custom_command(TARGET rtype POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${FETCHCONTENT_BASE_DIR}/sfml-src/extlibs/bin/x64/openal32.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}
    COMMAND_EXPAND_LISTS
  )
endif()



install(TARGETS rtype RUNTIME DESTINATION bin)
include(CPack)