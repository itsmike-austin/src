//============================================================================
// Name        : Queue.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <queue>

using namespace std;

int main() {
	queue<int> q;

	cout << "queue::back()" << endl;

	cout << "Adding 5 items to list using q.push(i+1)" << endl;

	for( int i=0 ; i < 5 ; ++i ) q.push(i+1);

	cout << "Last element of queue q = " << q.back() << endl;

	return 0;
}
