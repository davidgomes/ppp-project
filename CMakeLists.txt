project (ppp-project)
cmake_minimum_required (VERSION 2.8)

set(INCLUDE_DIR /headers/)
include_directories (${INCLUDE_DIR}) 

file (GLOB_RECURSE PLATFORMER_INCLUDES "headers/*.h")
file (GLOB_RECURSE PLATFORMER_SOURCES "src/*.c")

include_directories (PLATFORMER_INCLUDES)
add_executable (ppp-project ${PLATFORMER_SOURCES})
target_link_libraries (ppp-project ${SFML_LIBRARIES})
