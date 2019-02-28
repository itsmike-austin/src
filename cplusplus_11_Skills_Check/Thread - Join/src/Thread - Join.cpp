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

void foo() {
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void bar() {
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main() {
	std::cout << "starting helper...\n";
	std::thread helper1(foo);

	std::cout << "starting another helper...\n";
	std::thread helper2(bar);

	std::cout << "waiting for helpers to finish..." << std::endl;
	helper1.join();
	helper2.join();

	std::cout << "done!\n";
}
