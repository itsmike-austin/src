//============================================================================
// Name        : Typeinfo.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <typeinfo>

struct S {
	virtual void f();
};

int main() {
	S* p = (S*)NULL;

	try {
		std::cout << typeid(*p).name() << '\n';
	}catch( const std::bad_typeid& e) {
		std::cout << e.what() << '\n';
	}
	return 0;
}
