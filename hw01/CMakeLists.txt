cmake_minimum_required(VERSION 3.16)
project(hw01 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")

include(FetchContent)
set(FETCHCONTENT_BASE_DIR ${CMAKE_CURRENT_BINARY_DIR}/third_party)

FetchContent_Declare(
  csfml
  GIT_REPOSITORY https://github.com/SFML/CSFML.git
  GIT_TAG 2.5.2
)
FetchContent_MakeAvailable(csfml)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} PRIVATE csfml-graphics csfml-system csfml-window)


set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-flto")
add_executable(${PROJECT_NAME}-ir main.c)
target_link_libraries(${PROJECT_NAME}-ir PRIVATE csfml-graphics csfml-system csfml-window)
target_compile_options(${PROJECT_NAME}-ir PUBLIC -emit-llvm -flto)
