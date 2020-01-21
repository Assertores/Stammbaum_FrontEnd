cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

add_library(csv_parser
	csv_parser.hpp
	csv_parser.cpp
)

target_compile_features(csv_parser PUBLIC cxx_std_17)

target_include_directories(csv_parser PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

############################

add_executable(csv_test
	test.cpp
)

target_link_libraries(csv_test
	csv_parser
)

