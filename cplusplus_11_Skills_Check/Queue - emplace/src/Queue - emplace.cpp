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

	cout << "Adding 5 items to queue<int> using q.emplace(i);" << endl;

	for( int i=0 ; i < 5 ; ++i ) q.emplace(i);

	cout << "Contents of queue: ";
	while( !q.empty() ) {
		cout << q.front() << " ";
		q.pop();
	}
	cout << endl;

	return 0;
}
