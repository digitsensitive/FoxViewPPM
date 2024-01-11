# Set the minimum required version of cmake for this project
cmake_minimum_required(VERSION 3.5.0)

# Define the C11 standard whose features we request to build this project
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Set the project version
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_REVISION 0)
string(TIMESTAMP VERSION_YEAR "%Y")

# Set the project name with the corresponding version
project(ppm-viewer VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REVISION} LANGUAGES C)
message("Building for target: ${CMAKE_SYSTEM_NAME}")

################################
# SDL3
# https://github.com/libsdl-org/SDL/blob/main/docs/README-cmake.md
################################

# By default, SDL_SHARED is ON, and SDL_STATIC is OFF.
# In this example, I want to build and install a static SDL library, as
# I prefer not to include the SDL3.dll separately in the folder.
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)

# This assumes you have added SDL as a submodule in vendors/sdl
add_subdirectory(vendors/sdl EXCLUDE_FROM_ALL)

# Add our executable to our project
if (WIN32)
    configure_file("${PROJECT_SOURCE_DIR}/build/windows/ppm-viewer.rc.in" "${PROJECT_SOURCE_DIR}/build/windows/ppm-viewer.rc")
    set(PPM_VIEWER_SRC "${PROJECT_SOURCE_DIR}/build/windows/ppm-viewer.rc")
    add_executable(${PROJECT_NAME} WIN32
        src/main.c
        src/ppm.c
        src/sdl_engine.c
        src/sdl_renderer.c
        ${PPM_VIEWER_SRC})
endif()

target_include_directories(${PROJECT_NAME} PRIVATE include)

# Link to the actual SDL3 library.
# PRIVATE since it is for internal use only, others don't need to worry about it
# SDL3::SDL3 is an alias to either SDL3::SDL3-shared or SDL3::SDL3-static
# It picks the shared library in priority according to the CMake package.
# https://github.com/libsdl-org/SDL/blob/main/docs/README-cmake.md#including-sdl-in-your-project
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)