add_library(checkers_lib STATIC checkers.cpp checkers.h)
target_include_directories(checkers_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# add_executable(clara main.cpp)
# target_link_libraries(clara PRIVATE checkers_lib)

