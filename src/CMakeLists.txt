file(GLOB SRC_FILES "*.cpp")

add_library(jarvis_src STATIC ${SRC_FILES})

target_include_directories(jarvis_src PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(jarvis_src PUBLIC portaudio)  # Lier PortAudio dans la lib
