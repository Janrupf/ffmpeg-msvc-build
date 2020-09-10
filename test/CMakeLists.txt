# CMakeLists.txt
cmake_minimum_required(VERSION 3.0)
project(ffmpeg_test)

find_package(ffmpeg REQUIRED)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE ${FFMPEG_LIBRARIES})
target_include_directories(main PRIVATE ${FFMPEG_INCLUDE_DIRS})
install(TARGETS main DESTINATION bin)