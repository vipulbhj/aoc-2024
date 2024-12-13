#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <sstream>

int main() {
	std::string file_path = "./input.txt";
	std::ifstream infile(file_path);

	if (!infile.is_open()) {
		std::cerr << "Error: Could not open the file." << std::endl;
		return 1;
	}

	int num;
	int count;
	int errorsCount;
	int lineNums[100];
	int safeCountPartOne = 0;
	int safeCountPartTwo = 0;

	std::string line;
	while (std::getline(infile, line)) {
		std::stringstream ss(line);
		num = 0;
		count = 0;
		errorsCount = 0;
		std::memset(lineNums, 0, sizeof(lineNums));

		while (ss >> num) {
			lineNums[count++] = num;
		}

		int order = 0;
		for(int i = 1; i < count; ++i) {
			int diff = lineNums[i] - lineNums[i - 1];
			int absDiff = std::abs(diff);
			
			if(absDiff < 1 || absDiff > 3) ++errorsCount;
			else if(diff < 0 && order > 0) ++errorsCount;
			else if(diff > 0 && order < 0)  ++errorsCount;
			else if(order == 0 && diff < 0) order = -1;
			else if(order == 0 && diff > 0) order = 1;
		}

		if(errorsCount == 0) ++safeCountPartOne;

		if(errorsCount < 2) ++safeCountPartTwo;
	}

	std::cout << "Part One: " << safeCountPartOne << std::endl;
	std::cout << "Part Two: " << safeCountPartTwo << std::endl;

	return 0;
}
