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
	priority_queue<int> q;

	cout << "Adding 5 elements to an empty queue." << endl;

	for( int i=0 ; i < 5 ; ++i ) q.push(i);

	cout << "q.size(): " << q.size() << endl;

	return 0;
}
