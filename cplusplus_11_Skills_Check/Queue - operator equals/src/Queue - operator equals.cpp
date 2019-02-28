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
  // queue operator equals - copy version

  cout << "queue::= -- copy version." << endl;

  auto it1 = {1,2,3,4,5};
  auto it2 = {10,20};

  queue<int> q1(it1);
  queue<int> q2(it2);

  cout << "Original q1: ";
  for( auto ax = it1.begin() ; ax != it1.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  cout << "Original q2: ";
  for( auto ax = it2.begin() ; ax != it2.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  cout << "q2 = q1;" << endl;

  q2 = q1;

  cout << "Contents of q1: ";
  while( !q1.empty() ) {
    cout << q1.front() << " ";
    q1.pop();
  }
  cout << endl;

  cout << "Contents of q2: ";
  while( !q2.empty() ) {
    cout << q2.front() << " ";
    q2.pop();
  }
  cout << endl << endl;

  // queue operator equals - move version

  cout << "queue::= -- move version." << endl;

  q1.empty();
  q2.empty();

  for( auto ax=it1.begin() ; ax != it1.end() ; ++ax ) q1.push(*ax);
  for( auto ax=it2.begin() ; ax != it2.end() ; ++ax ) q2.push(*ax);

  cout << "Original q1: ";
  for( auto ax=it1.begin() ; ax != it1.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  cout << "Original q2: ";
  for( auto ax=it2.begin() ; ax != it2.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  cout << "q2 = move(q1);" << endl;

  q2 = move(q1);

  cout << "Contents of q1: ";
  while( !q1.empty() ) {
    cout << q1.front() << " ";
    q1.pop();
  }
  cout << endl;

  cout << "Contents of q2: ";
  while( !q2.empty() ) {
    cout << q2.front() << " ";
    q2.pop();
  }
  cout <<  endl;

  return 0;
}
