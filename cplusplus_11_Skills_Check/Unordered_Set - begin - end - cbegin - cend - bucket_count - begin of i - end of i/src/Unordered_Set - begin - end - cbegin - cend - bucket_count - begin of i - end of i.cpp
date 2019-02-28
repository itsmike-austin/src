//============================================================================
// Name        : Unordered_Set.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

//============================================================================
// Name        : Unordered_Set.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

int main()
{
  // Unordered_Set::begin - end

  unordered_set<string> us =
    {"100","200","300","400","500","600","700","800"};

  cout << "set contents: ";
  for(unordered_set<string>::iterator it = us.begin() ; it != us.end() ; ++it ) {
    cout << *it << " ";
  }
  cout << endl;

  cout << "for(i=0;i<set.bucket_count();++i)"                << endl;
  cout << "  for(auto lit=us.begin(i);lit!=us.end(i);++lit)" << endl;
  cout << "      cout << *lit (local iterator);"             << endl;

  cout << "sets buckets contain: " << endl;
  for(unsigned i=0 ; i < us.bucket_count() ; ++i ) {
    cout << "bucket #" << i << " contains: ";
    for(auto lit = us.begin(i) ; lit != us.end(i) ; ++lit ) {
      cout << *lit << " ";
    }
    cout << endl;
  }

  cout << endl;

  // Unordered_Set::cbegin - cend

  cout << "Unordered_Set::cbegin - cend." << endl;

  cout << "set contains: ";
  for(unordered_set<string>::const_iterator it = us.cbegin() ; it != us.cend() ; ++it ) {
    cout << *it << " ";
  }
  cout << endl;

  cout << "for(i=0;i<set.bucket_count();++i)"                  << endl;
  cout << "  for(auto lit=us.cbegin(i);lit!=us.cend(i);++lit)" << endl;
  cout << "      cout << *lit (local iterator);"               << endl;

  cout << "set buckets contain: " << endl;
  for( unsigned i=0 ; i < us.bucket_count() ; ++i ) {
    cout << "bucket #" << i << " contains: ";
    for( auto lit = us.cbegin(i) ; lit != us.cend(i) ; ++lit ) {
      cout << *lit << " ";
    }
    cout << endl;
  }

  cout << endl;

  return 0;
}
