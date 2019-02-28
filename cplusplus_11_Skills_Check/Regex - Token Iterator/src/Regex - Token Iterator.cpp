//============================================================================
// Name        : Regex.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <algorithm>
#include <iterator>
#include <regex>

int main() {
   std::string text = "Tutorialspoint india pvt ltd.";

   std::regex ws_re("\\s+");
   std::copy( std::sregex_token_iterator(text.begin(), text.end(), ws_re, -1),
      std::sregex_token_iterator(),
      std::ostream_iterator<std::string>(std::cout, "\n"));

   std::string html = "<p><a href=\"http://tutorialspoint.com\">google</a> "
      "< a HREF =\"http://indiabbc.com\">cppreference</a>\n</p>";
   std::regex url_re("<\\s*A\\s+[^>]*href\\s*=\\s*\"([^\"]*)\"", std::regex::icase);
   std::copy( std::sregex_token_iterator(html.begin(), html.end(), url_re, 1),
      std::sregex_token_iterator(),
      std::ostream_iterator<std::string>(std::cout, "\n"));
}
