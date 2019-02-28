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

	cout << "Pushing 5 elements into the queue - [1..5]" << endl;

	for( int i=0 ; i < 5 ; ++i ) q.push(i+1);

	cout << "Size of queue = " << q.size() << endl << endl;

	return 0;
}
