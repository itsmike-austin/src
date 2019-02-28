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
  stack<int> s1;
  stack<int> s2;

  // Stack operator equals - copy version

  cout << "Stack operator equals - copy version."
       << endl
       << "for(i=0;i<5;++i)s1.push(i+1);"
       << endl;

  for( int i=0 ; i < 5 ; ++i ) s1.push(i+1);

  cout << "s2 = s1;" << endl;

  s2 = s1;

  cout << "Contents of s2: ";
  while( !s2.empty() ) {
    cout << s2.top() << " ";
    s2.pop();
  }
  cout << endl << endl;

  // Stack operator equals - move version

  cout << "Stack operator equals - move version."
       << endl
       << "for(i=0;i<5;++i)s1.push(i+1);"
       << endl
       << "s2 = move(s1);"
       << endl;

  s2 = move(s1);

  cout << "Contents of s1: ";
  while( !s1.empty() ) {
    cout << s1.top() << " ";
    s1.pop();
  }
  cout << endl;

  cout << "Contents of s2: ";
  while( !s2.empty() ) {
    cout << s2.top() << " ";
    s2.pop();
  }
  cout << endl << endl;

  return 0;
}
