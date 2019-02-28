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

  cout << "priority_queue<int> q; q.emplace(n);" << endl;

  q.emplace(3);
  q.emplace(1);
  q.emplace(5);
  q.emplace(2);
  q.emplace(4);

  cout << "Queue contents are" << endl;
  while( !q.empty() ) {
    cout << q.top() << " ";
    q.pop();
  }
  cout << endl;

  return 0;
}
