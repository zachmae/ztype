include(FetchContent)
set(BUILD_SHARED_LIBS OFF)

FetchContent_Declare(SFML
 GIT_REPOSITORY https://github.com/SFML/SFML.git
 GIT_TAG 8f54a3e97c35476012613a8a41b7d2234d7ce38e
)

FetchContent_MakeAvailable(SFML)
