#include <iostream>
#include <utility>

#include "./csv_parser.hpp"

int main(void) {

	{
		std::string line = "asdf,addd";

		auto ret = csv_parser::parse_line<std::string, std::string>(line);

		std::cout << "0: " << std::get<0>(ret) << "\n";
		std::cout << "1: " << std::get<1>(ret) << "\n";
	}

	std::cout << std::string(40, '-') << "\n";

	{
		std::string line = "asdf,,addd";

		auto ret = csv_parser::parse_line<std::string, std::string, std::string>(line);

		std::cout << "0: " << std::get<0>(ret) << "\n";
		std::cout << "1: " << std::get<1>(ret) << "\n";
		std::cout << "2: " << std::get<2>(ret) << "\n";
	}

	std::cout << std::string(40, '-') << "\n";

	{
		std::string line = "asdf,false";

		auto ret = csv_parser::parse_line<std::string, bool>(line);

		std::cout << "0: " << std::get<0>(ret) << "\n";
		std::cout << "1: " << (std::get<1>(ret) ? "true" : "false") << "\n";
	}

	std::cout << std::string(40, '-') << "\n";

	{
		std::string line = "asdf,false,05.06.1999";

		auto ret = csv_parser::parse_line<std::string, bool, std::tm>(line);

		std::cout << "0: " << std::get<0>(ret) << "\n";
		std::cout << "1: " << (std::get<1>(ret) ? "true" : "false") << "\n";
		std::cout << "2: " << std::put_time(&std::get<2>(ret), "%d-%m-%Y") << "\n";
	}

	return 0;
}

