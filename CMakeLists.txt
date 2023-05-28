 cmake_minimum_required(VERSION 3.26)

 project(Chip-8-emulator)

 include_directories(headers)

 file(GLOB SOURCES "src/*.c")
 file(GLOB HEADERS "headers/*.h")
 add_executable(Chip-8-emulator ${SOURCES})
 target_link_libraries(Chip-8-emulator csfml-window csfml-graphics csfml-system csfml-audio)
