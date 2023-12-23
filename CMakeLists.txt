# Set the minimum required version of cmake for this project
cmake_minimum_required(VERSION 3.28.0)

# Define the C11 standard whose features we request to build this project
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Set the project version
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_REVISION 0)

# Set the project name with the corresponding version
project(ppm-viewer VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REVISION})

################################
# SDL3
################################

# This assumes you have added SDL as a submodule in vendors/sdl
add_subdirectory(vendors/sdl EXCLUDE_FROM_ALL)

# Add our executable to our project
add_executable(${PROJECT_NAME} WIN32 src/main.c)

# target_include_directories with ${SDL2_INCLUDE_DIRS} is not needed anymore
# If I have an include folder in my project, I should use it again

# Link to the actual SDL3 library.
# PRIVATE since it is for internal use only, others don't need to worry about it
# https://github.com/libsdl-org/SDL/blob/main/docs/README-cmake.md#including-sdl-in-your-project
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)