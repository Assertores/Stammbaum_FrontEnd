#pragma once

#pragma once

#include <csv_parser.hpp>

#include "types.h"

namespace csv_parser {

	template<>
	relType parse_entry(std::string_view string);

	template<>
	sexType parse_entry(std::string_view string);

} // csv_parser

