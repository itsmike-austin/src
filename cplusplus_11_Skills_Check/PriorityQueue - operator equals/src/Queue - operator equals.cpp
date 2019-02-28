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
  auto it1 = {3,1,5,2,4};
  auto it2 = {3,1,5};

  priority_queue<int> q1(less<int>(),it1);
  priority_queue<int> q2(less<int>(),it2);

  // priority_queue operator equals -- copy version

  cout << "priority_queue operator equals -- copy version." << endl;

  cout << "Original it1: ";
  while( !q1.empty() ) {
    cout << q1.top() << " ";
    q1.pop();
  }
  cout << endl;

  cout << "Original it2: ";
  while( !q2.empty() ) {
    cout << q2.top() << " ";
    q2.pop();
  }
  cout << endl;

  // Reload the queues.

  for( auto ax=it1.begin() ; ax != it1.end() ; ++ax ) q1.push(*ax);
  for( auto ax=it2.begin() ; ax != it2.end() ; ++ax ) q2.push(*ax);

  cout << "q1 = q2;" << endl;

  q1 = q2;

  cout << "Final it1: ";
  while( !q1.empty() ) {
    cout << q1.top() << " ";
    q1.pop();
  }
  cout << endl;

  cout << "Final it2: ";
  while( !q2.empty() ) {
    cout << q2.top() << " ";
    q2.pop();
  }
  cout << endl << endl;

  // priority_queue operator equals -- move version

  cout << "priority_queue operator equals -- move version." << endl;

  for( auto ax=it1.begin() ; ax != it1.end() ; ++ax ) q1.push(*ax);
  for( auto ax=it2.begin() ; ax != it2.end() ; ++ax ) q2.push(*ax);

  cout << "Original it1: ";
  while( !q1.empty() ) {
    cout << q1.top() << " ";
    q1.pop();
  }
  cout << endl;

  cout << "Original it2: ";
  while( !q2.empty() ) {
    cout << q2.top() << " ";
    q2.pop();
  }
  cout << endl;

  // Reload the queues.

  for( auto ax=it1.begin() ; ax != it1.end() ; ++ax ) q1.push(*ax);
  for( auto ax=it2.begin() ; ax != it2.end() ; ++ax ) q2.push(*ax);

  cout << "q1 = move(q2);" << endl;

  q1 = move(q2);

  cout << "Final it1: ";
  while( !q1.empty() ) {
    cout << q1.top() << " ";
    q1.pop();
  }
  cout << endl;

  cout << "Final it2: ";
  while( !q2.empty() ) {
    cout << q2.top() << " ";
    q2.pop();
  }
  cout << endl << endl;

  return 0;
}
