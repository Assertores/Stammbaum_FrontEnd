#include "types_parser.hpp"

namespace csv_parser {

	template<>
	relType parse_entry(std::string_view string) {
		if(string == "Father") {
			return Father;
		} else if(string == "Mother") {
			return Mother;
		} else if(string == "FosterMother") {
			return FosterMother;
		} else if(string == "Married") {
			return Married;
		}

		assert(false && "relation Type entry is neither");
	}

	template<>
	sexType parse_entry(std::string_view string) {
		if(string == "Male") {
			return Male;
		} else if(string == "Female") {
			return Female;
		} else if(string == "Deverce") {
			return Deverce;
		}

		assert(false && "sex Type entry is neither");
	}

} // csv_parser

