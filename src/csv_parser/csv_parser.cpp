#include "./csv_parser.hpp"

namespace csv_parser {

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

		return false;
	}

	template<>
	uint64_t parse_entry(std::string_view string) {
		size_t pos = 0;
		return stoll(std::string{string}, &pos);
	}

	template<>
	uint32_t parse_entry(std::string_view string) {
		size_t pos = 0;
		return (uint32_t)stoll(std::string{string}, &pos);
	}

	template<>
	std::tm parse_entry(std::string_view string) {
		std::istringstream ss{std::string{string}};

		std::tm tm;

		ss >> std::get_time(&tm, "%d.%m.%Y");

		return tm;
	}
} // csv_parser

