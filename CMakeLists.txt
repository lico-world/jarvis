cmake_minimum_required(VERSION 3.14)  # Needed for FetchContent_MakeAvailable

# Project name and version
project(Jarvis VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Use FetchContent to clone and build PortAudio
include(FetchContent)

FetchContent_Declare(
  portaudio
  GIT_REPOSITORY https://github.com/PortAudio/portaudio.git
  GIT_TAG        master
)

FetchContent_MakeAvailable(portaudio)

# Add your executable
add_executable(Jarvis main.cpp)

# Link with PortAudio
target_link_libraries(Jarvis PRIVATE portaudio)
