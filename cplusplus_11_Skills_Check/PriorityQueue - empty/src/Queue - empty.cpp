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

int main()
{
	priority_queue<int> q;

	cout << "q.empty() -- flag" << endl;

	if ( q.empty() ) cout << "priority_queue is empty" << endl;

	cout << "q.emplace(1);" << endl;

	q.emplace(1);

	if ( !q.empty() ) cout << "priority_queue is not empty" << endl;

	return 0;
}
