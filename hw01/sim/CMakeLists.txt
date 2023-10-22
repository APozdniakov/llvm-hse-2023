include(FetchContent)

FetchContent_Declare(
  csfml
  GIT_REPOSITORY https://github.com/SFML/CSFML.git
  GIT_TAG 2.5.2
)

FetchContent_GetProperties(csfml)
if(NOT csfml_POPULATED)
    FetchContent_Populate(csfml)
    add_subdirectory(${csfml_SOURCE_DIR} ${csfml_BINARY_DIR})
endif()

add_library(sim STATIC sim.c)
target_include_directories(sim PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(sim PRIVATE csfml-audio csfml-graphics csfml-system csfml-window)
