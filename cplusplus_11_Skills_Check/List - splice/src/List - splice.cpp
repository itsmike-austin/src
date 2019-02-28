//============================================================================
// Name        : List.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <list>

using namespace std;

int main()
{
  // list::splice

  list<int> l1 = {1,2,3};
  list<int> l2 = {4,5};

  cout << "list::splice()" << endl;
  cout << "Original l1: ";
  for ( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Original l2: ";
  for( auto it=l2.begin() ; it != l2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "l1.splice(l1.end(),12);" << endl;

  l1.splice(l1.end(),l2);

  cout << "Final list: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // list::splice - single element

  cout << "list::splice - single element." << endl;

  l1.clear();
  l2.clear();

  l1 = {1,2,3};
  l2 = {4,5};

  cout << "Original l1: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Original l2: ";
  for( auto it=l2.begin() ; it != l2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "l1.splice(l1.end(),l2,l2.begin());" << endl;

  l1.splice(l1.end(),l2,l2.begin());

  cout << "Final l1: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // list::splice - move version

  cout << "list::splice - move version." << endl;

  l1.clear();
  l2.clear();

  l1 = {1,2,3};
  l2 = {4,5};

  cout << "Original l1: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Original l2: ";
  for( auto it=l2.begin() ; it != l2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "l1.splice(l1.end(),move(l2));" << endl;

  l1.splice(l1.end(),move(l2));

  cout << "Final l1: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Final l2: ";
  for( auto it=l2.begin() ; it != l2.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // list::splice - range version

  cout << "list::splice - range version." << endl;

  l1.clear();
  l2.clear();

  l1 = {1,2};
  l2 = {3,4,5};

  cout << "Original l1: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Original l2: ";
  for( auto it=l2.begin() ; it != l2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "l1.splice(l1.end(),l2,l2.begin(),l2.end());" << endl;

  l1.splice(l1.end(),l2,l2.begin(),l2.end());

  cout << "Final l1: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  #if 0
  // list::splice - single element move version

  cout << "list::splice - single element move version." << endl;

  l1.clear();
  l2.clear();

  l1 = {1,2,3};
  l2 = {4,5};

  cout << "Original l1: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Original l2: ";
  for( auto it=l2.begin() ; it != l2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "l1.splice(l1.end(),move(l2),l2.begin());" << endl;

  l1.splice(l1.end(),move(12),l2.begin());

  cout << "Final l1: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;
#endif

  // list::splice - range and move version

  cout << "list::splice - range and move version." << endl;

  l1.clear();
  l2.clear();

  l1 = {1,2};
  l2 = {3,4,5};

  cout << "Original l1: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Original l2: ";
  for( auto it=l2.begin() ; it != l2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "l1.splice(l1.end(),move(l2),l2.begin(),l2.end());" << endl;

  l1.splice(l1.end(),move(l2),l2.begin(),l2.end());

  cout << "Final l1: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Final l2: ";
  for( auto it=l2.begin() ; it != l2.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  return 0;
}
