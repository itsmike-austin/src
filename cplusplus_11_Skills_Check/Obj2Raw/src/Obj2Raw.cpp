//============================================================================
// Name        : Obj2Raw.cpp
// Author      : MIke
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <stdint.h>

using namespace std;

class Spinlock {
	std::atomic_flag flag;
public:
	Spinlock(): flag(ATOMIC_FLAG_INIT) {}

	void lock() {
		while( flag.test_and_set() );
	}

	void unlock() {
		flag.clear();
	}
};

Spinlock spin;

void workOnResource(int n)
{
	spin.lock();
	cout << "locked and unlocking thread " << n << endl;
	// Shared resource
	spin.unlock();
}

int main() {
	std::thread *threadList = new std::thread[20];

	for( int i=0 ; i < 20 ; ++i ) {
		threadList[i] = std::thread(workOnResource,i);
	}

	for( int i=0 ; i < 20 ; ++i ) {
		threadList[i].join();
	}

	delete [] threadList;

	return 0;
}
