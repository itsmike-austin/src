//============================================================================
// Name        : Regex.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <regex>
#include <iterator>

int main()
{
	std::string s ("There is a subsequence in the string\n");
	std::regex e ("\\b(sub)([^ ]*)");

	std::cout << std::regex_replace(s,e,"sub-$2");

	std::string result;
	std:regex_replace(std::back_inserter(result),s.begin(),s.end(),e,"$2");
	std::cout << result;

	std::cout << std::regex_replace(s,e,"$1 and $2",std::regex_constants::format_no_copy);
	std::cout << std::endl;

	return 0;
}
