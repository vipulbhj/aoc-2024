#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

int main() {
	std::string file_path = "./input.txt";
	std::ifstream infile(file_path);

	int a, b;
	std::vector<int> first, second;
	while(infile >> a >> b) {
		first.push_back(a);
		second.push_back(b);
	}

	std::sort(first.begin(), first.end());
	std::sort(second.begin(), second.end());

	int partOne = 0;
	for(std::size_t i = 0; i < first.size(); ++i) {
		partOne += std::abs(second[i] - first[i]);
	}

	std::map<int, int> freq;
	for (int num : second) {
		freq[num]++;
	}

	int partTwo = 0;
	for (int num : first) {
		partTwo += num * freq[num];
	}

	std::cout << "Part One: " << partOne << std::endl;
	std::cout << "Part Two: " << partTwo << std::endl;

	return 0;
}
