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

	cout << "adding 5 to queue using q.emplace / could use q.push as well" << endl;

	for( int i=0 ; i < 5 ; ++i ) q.emplace(i+1);

	cout << "First element of queue from q.front() = " << q.front() << endl;

	cout << "The queue contents are: ";
	while( !q.empty() ) {
		cout << q.front() << " ";
		q.pop();
	}
	cout << endl;

	return 0;
}
