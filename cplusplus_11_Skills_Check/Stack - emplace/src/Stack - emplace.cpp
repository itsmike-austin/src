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
  stack<int> s;

  cout << "Stack - emplace"
       << endl
       << "for(i=0;i<5;++i)stack.emplace(i+1);"
       << endl;

  for( int i=0 ; i < 5 ; ++i ) s.emplace(i+1);

  cout << "Final stack contents using stack.top: ";
  while( !s.empty() ) {
    cout << s.top() << " ";
    s.pop();
  }
  cout << endl;

  return 0;
}
