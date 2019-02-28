//============================================================================
// Name        : ForwardList.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <forward_list>

using namespace std;

int main()
{
  cout << "splice_after(), splice_after() - move version" << endl;
  cout << "splce_after() - single version, splice_after() - single element move version." << endl;
  cout << "splice_after() - range version." << endl << endl;

  forward_list<int> fl1 = {2,3,4};
  forward_list<int> fl2 = {1,5};

  // Basic splice after location

  cout << "splice_after -- basic version." << endl;
  cout << "Original fl1: ";
  for( auto it=fl1.begin() ; it != fl1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Original fl2: ";
  for( auto it=fl2.begin() ; it != fl2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout <<  "fl2.splice_after(fl2.begin(),fl1);" << endl;

  fl2.splice_after(fl2.begin(),fl1);

  cout << "Final fl2: ";
  for( auto it=fl2.begin() ; it != fl2.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // splice_after -- move version.

  cout << "splice_after -- move version." << endl;

  fl1.clear();
  fl2.clear();
  fl1 = {2,3,4};
  fl2 = {1,5};

  cout << "fl2.splice_after(fl2.begin(),move(fl1));" << endl;

  cout << "Original fl1: ";
  for( auto it=fl1.begin() ; it != fl1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Original fl2: ";
  for( auto it=fl2.begin() ; it != fl2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  fl2.splice_after(fl2.begin(),move(fl1));

  cout << "Final fl1: ";
  for( auto it=fl1.begin() ; it != fl1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Final fl2: ";
  for( auto it=fl2.begin() ; it != fl2.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // splice_after -- single_element

  cout << "splice_after() -- single element." << endl;

  fl1.clear();
  fl2.clear();

  fl1 = {1,2};
  fl2 = {1,3,4,5};

  cout << "Original fl1: ";
  for( auto it=fl1.begin() ; it != fl1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Original fl2: ";
  for( auto it=fl2.begin() ; it != fl2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "fl2.splice_after(f12.begin(),fl1,fl1.begin());" << endl;

  fl2.splice_after(fl2.begin(),fl1,fl1.begin());

  cout << "Final fl1: ";
  for( auto it=fl1.begin() ; it != fl1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Final fl2: ";
  for( auto it=fl2.begin() ; it != fl2.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // splice_after -- single element move version

  cout << "splice_after() -- single element move version." << endl;

  fl1.clear();
  fl2.clear();

  fl1 = {1,2};
  fl2 = {1,3,5,6};

  cout << "Original fl1: ";
  for( auto it=fl1.begin() ; it != fl1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Original fl2: ";
  for( auto it=fl2.begin() ; it != fl2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "fl2.splice_after(fl2.begin(),move(fl1),fl1.begin());" << endl;

  fl2.splice_after(fl2.begin(),move(fl1),fl1.begin());

  cout << "Final fl1: ";
  for( auto it=fl1.begin() ; it != fl1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Final fl2: ";
  for( auto it=fl2.begin() ; it != fl2.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // splice_after -- range version

  cout << "splice_after -- range version" << endl;

  fl1.clear();
  fl2.clear();

  fl1 = {1,2,3,4};
  fl2 = {1,5};

  cout << "Original fl1: ";
  for( auto it=fl1.begin() ; it != fl1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Original fl2: ";
  for( auto it=fl2.begin() ; it != fl2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "fl2.splice_after(fl2.begin(),fl1,fl1.begin(),fl1.end());" << endl;

  fl2.splice_after(fl2.begin(),fl1,fl1.begin(),fl1.end());

  cout << "Final fl1: ";
  for( auto it=fl1.begin() ; it != fl1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Final fl2: ";
  for( auto it=fl2.begin() ; it != fl2.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // splice_after -- range and move version

  cout << "splice_after() -- range and move version." << endl;

  fl1.clear();
  fl2.clear();

  fl1 = {1,2,3,4};
  fl2 = {1,5};

  cout << "Original fl1: ";
  for( auto it=fl1.begin() ; it != fl1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Original fl2: ";
  for( auto it=fl2.begin() ; it != fl2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "fl2.splice_after(fl2.begin(),move(fl1),fl1.begin(),fl1.end());" << endl;

  fl2.splice_after(fl2.begin(),move(fl1),fl1.begin(),fl1.end());

  cout << "Final fl1: ";
  for( auto it=fl1.begin() ; it != fl1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Final fl2: ";
  for( auto it=fl2.begin() ; it != fl2.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  return 0;
}
