cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

add_library(csv_parser
	csv_parser.hpp
	csv_parser.cpp
)

############################

add_executable(csv_test
	test.cpp
)

target_link_libraries(csv_test
	csv_parser
)

