add_executable(clara-tests test-main.cpp checkers_test.cpp)
target_link_libraries(clara-tests PRIVATE catch checkers-lib)

