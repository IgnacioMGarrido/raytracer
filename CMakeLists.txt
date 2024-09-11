cmake_minimum_required(VERSION 3.5)
project(raytracer)

add_subdirectory(vendor/sdl EXCLUDE_FROM_ALL)
# Create your game executable target as usual
set(SOURCES vendor/qbLinAlg/qbVector4.hpp vendor/qbLinAlg/qbVector.h vendor/qbLinAlg/qbVector2.hpp vendor/qbLinAlg/qbVector3.hpp vendor/qbLinAlg/qbMatrix33.hpp vendor/qbLinAlg/qbMatrix44.hpp vendor/qbLinAlg/qbPCA.h vendor/qbLinAlg/qbQR.h vendor/qbLinAlg/qbLinSolve.h vendor/qbLinAlg/qbLSQ.h vendor/qbLinAlg/qbMatrix.h vendor/qbLinAlg/qbEIG.h)
set(RAYTRACER src/raytracer/RTImage.h src/raytracer/RTImage.cpp)
add_executable(raytracer src/main.cpp src/CApp.cpp src/CApp.h ${RAYTRACER} ${SOURCES})

target_include_directories(raytracer PRIVATE vendor/qbLinAlg)

# Link to the actual SDL2 library. SDL2::SDL2 is the shared SDL library, SDL2::SDL2-static is the static SDL libarary.
target_link_libraries(raytracer SDL2::SDL2 SDL2::SDL2main)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET raytracer PROPERTY CXX_STANDARD 20)
endif()