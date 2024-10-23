cmake_minimum_required(VERSION 3.27)
project(test3DCube)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

#SDL2
set(SDL2_PATH "SDL2-2.30.7\\x86_64-w64-mingw32")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

#SDL2_Image
set(SDL2_IMAGE_PATH "SDL2_image-2.8.2\\x86_64-w64-mingw32")
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(test3DCube main.cpp
        Cube.h
        Cube.cpp
        LineManager.cpp
        LineManager.h
        TwoDMathManager.cpp
        TwoDMathManager.h
        InputHandler.h
        InputHandler.cpp)

target_link_libraries(test3DCube ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES})