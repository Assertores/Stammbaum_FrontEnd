#pragma once

#include <string>
#include <string_view>
#include <tuple>
#include <iomanip>
#include <sstream>
#include <cassert>

namespace csv_parser {

	template<typename T>
	T parse_entry(std::string_view string);

	template<typename T, typename... A>
	std::tuple<T, A...> parse_line(std::string_view line_segment) {
		auto comma_pos = line_segment.find_first_of(',');

		if constexpr (sizeof...(A) > 0) {
			assert(comma_pos != line_segment.npos);

			return std::tuple_cat(
					parse_line<T>(line_segment.substr(0, comma_pos)),
					parse_line<A...>(line_segment.substr(comma_pos+1))
				);
		} else {
			assert(comma_pos == line_segment.npos);

			return std::tuple<T>(parse_entry<T>(line_segment));
		}
	}

	template<>
	std::string parse_entry(std::string_view string);

	template<>
	bool parse_entry(std::string_view string);

	template<>
	uint64_t parse_entry(std::string_view string);

	template<>
	uint32_t parse_entry(std::string_view string);

	template<>
	std::tm parse_entry(std::string_view string);

} // csv_parser

