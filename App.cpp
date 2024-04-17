#include "TestExtins.h"
#include "TestScurt.h"
#include <chrono>


#include <iostream>
using namespace std;


int main() {
	auto start = std::chrono::high_resolution_clock::now();

	testAll();
	cout << "Testele scurte s-au finalizat" << endl;
	testAllExtins();
	cout << "Testele extinse s-au finalizat" << endl;
	cout << "That's all!" << endl;

	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> duration = end - start;
	double seconds = duration.count();

	std::cout << "Procesul a durat " << seconds << " secunde.\n";

	int minutes = static_cast<int>(seconds / 60);
	double remainingSeconds = seconds - minutes * 60;

	std::cout << seconds << " secunde sunt aproximativ " << minutes << " minute si " << remainingSeconds << " secunde." << std::endl;

	return 0;
}

