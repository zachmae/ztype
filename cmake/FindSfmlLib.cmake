include(FetchContent)
set(BUILD_SHARED_LIBS ON)

FetchContent_Declare(SFML
 GIT_REPOSITORY https://github.com/SFML/SFML.git
 GIT_TAG c1064bae925693667c7a34cad264bd5ea3ece177
)

FetchContent_MakeAvailable(SFML)
