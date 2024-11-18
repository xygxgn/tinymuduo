cmake_minimum_required(VERSION 3.0.2)
project(tinymuduo)

add_compile_options(-std=c++11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 
  ${CMAKE_CURRENT_LIST_DIR}/bin
)

include_directories(
  include
)

add_executable(timestamp 
  ${CMAKE_CURRENT_LIST_DIR}/src/Timestamp.cc
)

target_link_libraries(
  timestamp
)
