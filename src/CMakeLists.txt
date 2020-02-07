cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

add_subdirectory(./csv_parser)

add_library(sb_utility
STATIC
	utility/types.h
	utility/types_parser.hpp
	utility/types_parser.cpp
	utility/stringCollection.h
	utility/printer.h
	utility/printer.cpp
)

target_compile_features(sb_utility PUBLIC cxx_std_17)
target_link_libraries(sb_utility PUBLIC csv_parser)

################################

add_library(sb_backend
	backend/dataHandler.h
	backend/dataHandler.cpp
)

target_compile_features(sb_backend PUBLIC cxx_std_17)
target_link_libraries(sb_backend
PUBLIC
	csv_parser
	sb_utility
)

################################

add_library(sb_frontend
	frontend/treeBuilderElement.h
	frontend/treeBuilderElement.cpp
	frontend/calculate.h
	frontend/calculate.cpp
	frontend/MLMSElement.h
	frontend/MLMSElement.cpp
)

target_compile_features(sb_frontend PUBLIC cxx_std_17)
target_link_libraries(sb_frontend PUBLIC sb_utility)

################################

add_executable(sb_test1
	sb_test1.cpp
)

set_target_properties(sb_test1 PROPERTIES LINKER_LANGUAGE CXX DEBUG_POSTFIX "_debug")

target_link_libraries(sb_test1
PRIVATE
	sb_utility
	sb_backend
	sb_frontend
)

################################

add_executable(sb_cli
	mainCLI.cpp
)

set_target_properties(sb_cli PROPERTIES LINKER_LANGUAGE CXX DEBUG_POSTFIX "_debug")

target_link_libraries(sb_cli
PRIVATE
	sb_utility
	sb_backend
	sb_frontend
)
