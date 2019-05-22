add_library(checkers-lib STATIC checkers/checkers.cpp checkers/checkers.h)
target_include_directories(checkers-lib PUBLIC ${CMAKE_SOURCE_DIR}/src/checkers)

