#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <sstream>

std::map<int, std::vector<int>> pageOrder;

bool customComparator(int a, int b)
{
	auto aa = pageOrder[a];
	auto bb = pageOrder[b];

	if (std::find(aa.begin(), aa.end(), b) != aa.end())
		return true;

	return false;
}

int main()
{
	auto partOneCount = 0;
	auto partTwoCount = 0;

	std::string file_path = "./input.txt";
	std::ifstream infile(file_path);

	if (!infile.is_open())
	{
		std::cerr << "Error: Could not open the file." << std::endl;
		return 1;
	}

	std::string line;
	bool ruleLine = true;
	while (std::getline(infile, line))
	{
		if (line.empty())
		{
			ruleLine = false;
			continue;
		}

		std::stringstream ss(line);
		if (ruleLine)
		{
			char _p;
			int first, second;
			while (ss >> first >> _p >> second)
			{
				pageOrder[first].push_back(second);
			}
		}
		else
		{
			std::vector<int> nums;
			std::string token;

			while (std::getline(ss, token, ','))
			{
				nums.push_back(std::stoi(token));
			}

			bool valid = true;
			for (int i = 0; i < (int)nums.size(); ++i)
			{
				auto container = pageOrder[nums[(size_t)i]];
				if (container.empty() && i != (int)nums.size() - 1)
				{
					valid = false;
					break;
				}

				if (i < (int)nums.size() - 2)
				{

					if (std::find(container.begin(), container.end(), (size_t)nums[(size_t)(i + 1)]) == container.end())
					{
						valid = false;
						break;
					}
				}
			}
			if (valid)
			{
				auto middle = (nums.size() / 2);
				partOneCount += nums.at(middle);
			}

			if (!valid)
			{
				std::sort(nums.begin(), nums.end(), customComparator);
				auto middle = (nums.size() / 2);
				partTwoCount += nums.at(middle);
			}
		}
	}

	std::cout << "Part One: " << partOneCount << std::endl;
	std::cout << "Part Two: " << partTwoCount << std::endl;

	return 0;
}
