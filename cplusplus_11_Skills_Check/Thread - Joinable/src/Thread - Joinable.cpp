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
	std::this_thread::sleep_for(std::chrono::seconds(2));
}

int main() {
	std::thread t;
	std::cout << "before joinable: " << t.joinable() << '\n';

	t = std::thread(foo);
	std::cout << "after joinable: " << t.joinable() << '\n';

	t.join();
	std::cout << "after joining, joinable: " << t.joinable() << '\n';

	return 0;
}
