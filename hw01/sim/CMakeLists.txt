include(FetchContent)
set(FETCHCONTENT_BASE_DIR ${CMAKE_CURRENT_BINARY_DIR}/third_party)

FetchContent_Declare(
  csfml
  GIT_REPOSITORY https://github.com/SFML/CSFML.git
  GIT_TAG 2.5.2
)
FetchContent_MakeAvailable(csfml)

add_library(sim STATIC sim.c)
target_include_directories(sim PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(sim PRIVATE csfml-audio csfml-graphics csfml-system csfml-window)
