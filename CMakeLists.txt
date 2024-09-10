cmake_minimum_required(VERSION 3.5)
project(raytracer)

add_subdirectory(vendor/sdl EXCLUDE_FROM_ALL)

# Create your game executable target as usual
add_executable(raytracer src/main.cpp)

# Link to the actual SDL2 library. SDL2::SDL2 is the shared SDL library, SDL2::SDL2-static is the static SDL libarary.
target_link_libraries(raytracer SDL2::SDL2 SDL2::SDL2main)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET raytracer PROPERTY CXX_STANDARD 20)
endif()