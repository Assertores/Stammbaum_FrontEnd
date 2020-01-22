cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

add_subdirectory(./csv_parser)

add_executable(sb_test1
	utility/types.h
	utility/types_parser.hpp
	utility/types_parser.cpp
	utility/stringCollection.h
	utility/printer.h
	utility/printer.cpp

	backend/dataHandler.h
	backend/dataHandler.cpp

	frontend/treeBuilderElement.h
	frontend/treeBuilderElement.cpp
	frontend/calculate.h
	frontend/calculate.cpp
	frontend/MLMSElement.h
	frontend/MLMSElement.cpp

	#sb_test1.cpp
	mainCLI.cpp
)

target_link_libraries(sb_test1 PRIVATE csv_parser)

