cmake_minimum_required(VERSION 3.0.2)
project(tinymuduo)

add_compile_options(-std=c++11)

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR}/lib)

set(EXECUTABLE_OUTPUT_PATH 
  ${CMAKE_CURRENT_LIST_DIR}/bin
)

include_directories(
  include
)

# file(GLOB_RECURSE PROJECT_SOURCE_FILES ${CMAKE_CURRENT_LIST_DIR}/src/*.cc)
# add_library(tinymuduo SHARED
#   ${PROJECT_SOURCE_FILES}
# )

aux_source_directory(./src SRC_LIST)
add_library(tinymuduo SHARED
  ${SRC_LIST}
)

add_executable(
  test
  example/test.cc
)

target_link_libraries(
  test
  tinymuduo
  pthread
)

