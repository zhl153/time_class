
#include"SFTestHarness.hpp"
#include<iostream>
using namespace SoftwareFoundations;

int main() {
	SFTestHarness mytest;
	int result = mytest.runAllTests();
	std::cout << result << " error" << std::endl;
	//_CrtDumpMemoryLeaks();
	return 0;
}
