set (PROJECT_NAME "ppp-project")

project (${PROJECT_NAME})
cmake_minimum_required (VERSION 2.8)

set (INCLUDE_DIR ./include/)
include_directories (${INCLUDE_DIR}) 

file (GLOB_RECURSE PLATFORMER_INCLUDES "include/*.h")
file (GLOB_RECURSE PLATFORMER_SOURCES "src/*.c")

include_directories (PLATFORMER_INCLUDES)
add_executable (${PROJECT_NAME} ${PLATFORMER_SOURCES})
target_link_libraries (${PROJECT_NAME} ${SFML_LIBRARIES})
