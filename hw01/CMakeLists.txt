cmake_minimum_required(VERSION 3.16)
project(hw01 LANGUAGES C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(sim)
get_target_property(SIM_INCLUDE_DIR sim INCLUDE_DIRECTORIES)

set(SOURCE main.c life.c)

add_executable(${PROJECT_NAME} ${SOURCE})
target_include_directories(${PROJECT_NAME} PUBLIC ${SIM_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC sim)

add_library(${PROJECT_NAME}-ir OBJECT ${SOURCE})
target_include_directories(${PROJECT_NAME}-ir PUBLIC ${SIM_INCLUDE_DIR})
target_compile_options(${PROJECT_NAME}-ir PUBLIC -S -emit-llvm)
