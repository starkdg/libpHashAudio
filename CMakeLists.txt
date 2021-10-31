cmake_minimum_required(VERSION 2.8)
project(pHashAudio)

set(pHashAudio_VERSION_MAJOR 1)
set(pHashAudio_VERSION_MINOR 0)

if (CMAKE_HOST_WIN32)
#  set windows variables here:
   message("win32 system detected")
   add_definitions(-g -Wall -O3)
   set(BUILD_DLL 1)
endif(CMAKE_HOST_WIN32)

if (CMAKE_HOST_UNIX)
# set unix system variables
   message("unix system detected")
   add_definitions(-g -Wall -O3)
endif(CMAKE_HOST_UNIX)

include_directories("${PROJECT_BINARY_DIR}")

add_library(pHashAudio SHARED AudioHash.c kiss_fft.c kiss_fftr.c)
target_link_libraries(pHashAudio m)

add_executable(TestpHashAudio TestAudioHash.c)
target_link_libraries(TestpHashAudio pHashAudio)

#tests
enable_testing()
add_test(NAME testproject COMMAND TestpHashAudio)

#install files
install(TARGETS pHashAudio DESTINATION bin)
install(FILES AudioHash.h DESTINATION include)

