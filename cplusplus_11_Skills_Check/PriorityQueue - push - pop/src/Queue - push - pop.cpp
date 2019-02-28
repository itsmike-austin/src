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
  // priority_queue::pop

  auto it = {3,1,5,2,4};
  priority_queue<int> qa(less<int>(),it);

  cout << "priority_queue::pop." << endl;

  cout << "Original queue: ";
  for( auto ax=it.begin() ; ax != it.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  cout << "while(!q.empty()){cout << q.top; q.pop();}" << endl;

  while( !qa.empty() ) {
    cout << qa.top() << " ";
    qa.pop();
  }

  cout << "queue is not empty." << endl << endl;

  // priority_queue::push -- copy version

  priority_queue<int> q;

  cout << "priority_queue::push -- copy version." << endl;

  cout << "for( int i=0 ; i < 5 ; ++i ) q.push(i+1);" << endl;

  for( int i=0 ; i < 5 ; ++i ) q.push(i+1);

  cout << "Queue contents are ";
  while( !q.empty() ) {
    cout << q.top() << " ";
    q.pop();
  }
  cout << endl << endl;

  // priority_queue::push -- move version

  cout << "priority_queue::push -- move version." << endl;

  auto it1 = {3,1,5,2,4};

  priority_queue<int> q1(less<int>(),it1);
  priority_queue<int> q2;

  cout << "Original queue contents: ";
  for(auto ax=it1.begin() ; ax != it1.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  cout << "for(i=0;i<5;++i){q2.push(move(q1.top()));q1.pop();}" << endl;

  for( int i=0 ; i < 5 ; ++i ) {
    q2.push(move(q1.top()));
    q1.pop();
  }

  cout << "Contents of q1: ";
  while( !q1.empty() ) {
    cout << q1.top() << " ";
    q1.pop();
  }
  cout << endl;

  cout << "Contents of q2: ";
  while( !q2.empty() ) {
    cout << q2.top() << " ";
    q2.pop();
  }
  cout << endl << endl;

  return 0;
}
