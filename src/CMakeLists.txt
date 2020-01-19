cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

add_subdirectory(./csv_parser)

add_executable(sb_test1
	utility/types.h
	utility/printer.h
	utility/printer.cpp

	backend/dataHandler.h
	backend/dataHandler.cpp

	sb_test1.cpp
	#mainCLI.cpp
)
