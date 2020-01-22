#include "types_parser.hpp"

namespace csv_parser {

	template<>
	relType parse_entry(std::string_view string) {
		if(string == "Father" ||
		   string == "father") {
			return Father;
		} else if(string == "Mother" ||
				  string == "mother") {
			return Mother;
		} else if(string == "FosterMother" ||
				  string == "fosterMother") {
			return FosterMother;
		} else if(string == "Married" ||
				  string == "married") {
			return Married;
		}

		assert(false && "relation Type entry is neither");
	}

	template<>
	sexType parse_entry(std::string_view string) {
		if(string == "Male" ||
		   string == "male") {
			return Male;
		} else if(string == "Female" ||
				  string == "female") {
			return Female;
		} else if(string == "Deverce" ||
				  string == "deverce") {
			return Deverce;
		}

		assert(false && "sex Type entry is neither");
	}

} // csv_parser

