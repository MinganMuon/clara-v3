add_library(checkers-lib STATIC checkers/checkers.cpp checkers/checkers.h)
target_include_directories(checkers-lib PUBLIC ${CMAKE_SOURCE_DIR}/src/checkers)

add_library(ui-lib STATIC ui-framework/ui-framework.h ui-framework/ui-framework.cpp)
target_include_directories(ui-lib PUBLIC ${CMAKE_SOURCE_DIR}/src/ui-framework)
find_package(Curses REQUIRED)
target_include_directories(ui-lib PRIVATE ${CURSES_INCLUDE_DIR})
target_link_libraries(ui-lib PRIVATE ${CURSES_LIBRARIES})

add_executable(clara main-ui/main.cpp)
target_link_libraries(clara PRIVATE ui-lib checkers-lib)

