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
  // queue::push -- copy version

  cout << "queue::push -- copy version." << endl;

  queue<int> q;

  cout << "for(i=0;i<5;++i) q.push(i+1);" << endl;

  for( int i=0 ; i < 5 ; ++i ) q.push(i+1);

  cout << "Contents of queue: ";
  while( !q.empty() ) {
    cout << q.front() << " ";
    q.pop();
  }
  cout << endl << endl;

  // queue::push -- move version

  cout << "queue::push -- move version." << endl;

  queue<int> q1;
  queue<int> q2;

  cout << "add 5 elements to q1" << endl;

  for( int i=0 ; i < 5 ; ++i ) q1.push(i+1);

  cout << "q1.push(move(q1.front()));" << endl;

  while( !q1.empty() ) {
    q2.push(move(q1.front()));
    q1.pop();
  }

  cout << "Contents of queue: ";
  while( !q2.empty() ) {
    cout << q2.front() << " ";
    q2.pop();
  }
  cout << endl << endl;

  // queue::pop

  cout << "queue::pop" << endl;

  while( !q.empty() ) q.pop();


  cout << "Pushing 5 onto queue [1..5]." << endl;

  for( int i=0 ; i < 5 ; ++i ) q.push(i);

  cout << "q.pop(); q.pop();" << endl;

  q.pop();
  q.pop();

  cout << "Contents of queue: ";
  while( !q.empty() ) {
    cout << q.front() << " ";
    q.pop();
  }
  cout << endl << endl;

  return 0;
}
