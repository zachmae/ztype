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

#Client executable generation
add_executable(${PROJECT_NAME}

        src/User/Scenes/Game/Init.cpp

        src/main_client.cpp
        src/main_server.cpp
        src/Network/Server.cpp
        src/Network/Client.cpp

        src/User/Systems/AnimationSystem.cpp
        src/User/Systems/DisplaySystem.cpp
        src/User/Systems/EventSystem.cpp
        src/User/Systems/PositionSystem.cpp

        )

target_link_libraries(${PROJECT_NAME}
    sfml-window
    sfml-graphics
    sfml-network
    sfml-audio
    sfml-system
    nlohmann_json::nlohmann_json
)

#Server executable generation
#add_executable(Server
#    src/main_server.cpp
#    src/Network/Server.cpp
#)
#
#target_link_libraries(Server
#    sfml-network
#    sfml-system
#)

include_directories(#includes
                    modules
                    src)


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
