//============================================================================
// Name        : Deque.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <deque>

using namespace std;

int main()
{
	deque<int> d(10);

	cout << "Initial size of deque = " << d.size() << endl;

	d.resize(5);

	cout << "size of deque after resize operation = " << d.size() << endl;

	d.shrink_to_fit();

	cout << "Size after d.shrink_to_fit(): " << d.size() << endl;

  return 0;
}
