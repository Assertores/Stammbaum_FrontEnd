#pragma once

//#include <fstream>
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
	std::string parse_entry(std::string_view string) {
		return std::string{string};
	}

	template<>
	bool parse_entry(std::string_view string) {
		if (string == "true") {
			return true;
		} else if (string == "false") {
			return false;
		}

		assert(false && "bool entry is neither");
	}

	template<>
	uint64_t parse_entry(std::string_view string) {
		size_t pos = 0;
		return stoll(std::string{string}, &pos);
	}

	template<>
	uint32_t parse_entry(std::string_view string) {
		size_t pos = 0;
		return stoll(std::string{string}, &pos);
	}

	template<>
	std::tm parse_entry(std::string_view string) {
		std::istringstream ss{std::string{string}};

		std::tm tm;

		ss >> std::get_time(&tm, "%d.%m.%Y");

		return tm;
	}
}

