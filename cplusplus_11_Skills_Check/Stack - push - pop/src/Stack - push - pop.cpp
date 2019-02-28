//============================================================================
// Name        : Stack.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stack>

using namespace std;

int main()
{
  // Stack push -- copy version

  cout << "Stack push -- copy version."
       << endl
       << "for(i=0;i<5;++i)s.push(i+1);"
       << endl;

  stack<int> s;

  for( int i=0 ; i < 5 ; ++i ) s.push(i+1);

  cout << "Stack contents are: ";
  while( !s.empty() ) {
    cout << s.top() << " ";
    s.pop();
  }
  cout << endl << endl;

  // Stack push -- move version

  cout << "Stack push -- move version."
       << endl
       << "for(i=0;i<5;++i)s1.push(i+1);"
       << endl;

  stack<int> s1;
  stack<int> s2;

  for( int i=0 ; i < 5 ; ++i ) s1.push(i+1);

  cout << "s2 = move(s1);" << endl;

  s2 = move(s1);

  cout << "Final s1: ";
  while( !s1.empty() ) {
    cout << s1.top() << " ";
    s1.pop();
  }
  cout << endl;

  cout << "Final s2: ";
  while( !s2.empty() ) {
    cout << s2.top() << " ";
    s2.pop();
  }
  cout << endl << endl;

  // Stack pop

  cout << "Stack pop"
       << endl
       << "for(i=0;i<5;++i)s.push(i+1);"
       << endl;

  for(int i=0 ; i < 5 ; ++i ) s.push(i+1);

  cout << "s.pop() removes the top element." << endl;

  cout << "Final stack: ";
  while( !s.empty() ) {
    cout << s.top() << " ";
    s.pop();
  }
  cout << endl << endl;

  return 0;
}

