//============================================================================
// Name        : Typeinfo.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <typeinfo>

struct Foo { virtual ~Foo() {} };
struct Bar { virtual ~Bar() {} };

int main() {
	Bar b;

	try {
		Foo& f = dynamic_cast<Foo&>(b);
	}catch( const std::bad_cast& e) {
		std::cout << e.what() << '\n';
	}
	return 0;
}
