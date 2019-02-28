//============================================================================
// Name        : Thread.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <thread>
#include <chrono>

void independentThread() {
	std::cout << "Starting thread.\n";
	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::cout << "Exiting previous thread.\n";
}

void threadCaller() {
	std::cout << "Starting thread caller.\n";
	std::thread t(independentThread);
	t.detach();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "Exiting thread caller\n";
}

int main() {
	threadCaller();
	std::this_thread::sleep_for(std::chrono::seconds(5));
	return 0;
}
