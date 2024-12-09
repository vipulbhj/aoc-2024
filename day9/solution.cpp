#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <sstream>

using Pair = std::pair<size_t, size_t>;

long long part_one_sol(size_t len, std::vector<int> nums, std::vector<int> spaces)
{
	size_t nums_idx = 0;
	size_t space_idx = 0;
	bool is_space = false;
	std::vector<int> row(len);

	for (size_t i = 0; i < len;)
	{
		size_t freq;
		size_t local_idx;

		if (!is_space)
		{
			local_idx = nums_idx;
			freq = static_cast<size_t>(nums[nums_idx++]);
		}
		else
		{
			local_idx = static_cast<size_t>(-1);
			freq = static_cast<size_t>(spaces[space_idx++]);
		}

		for (size_t j = 0; j < freq; ++j)
		{
			row[i + j] = static_cast<int>(local_idx);
		}
		i += freq;
		is_space = !is_space;
	}

	size_t back_idx = len - 1;
	for (size_t i = 0; i < len; ++i)
	{
		if (row[i] == -1)
		{
			while (back_idx > i && row[back_idx] == -1)
			{
				--back_idx;
			}
			if (back_idx > i)
			{
				row[i] = row[back_idx];
				row[back_idx] = -1;
				--back_idx;
			}
		}
	}

	long long part_one = 0;
	for (size_t i = 0; i < len; ++i)
	{
		if (row[i] == -1)
			continue;

		part_one += row[i] * (int)i;
	}

	return part_one;
}

long long part_two_sol(size_t len, std::vector<int> nums, std::vector<int> spaces)
{
	size_t nums_idx = 0;
	size_t space_idx = 0;
	bool is_space = false;
	std::vector<int> row(len);

	std::vector<Pair> chunks;
	std::vector<Pair> free_spaces;

	for (size_t i = 0; i < len;)
	{
		size_t freq;
		size_t local_idx;

		if (!is_space)
		{
			local_idx = nums_idx;
			freq = static_cast<size_t>(nums[nums_idx++]);
			chunks.push_back({i, freq});
		}
		else
		{
			local_idx = static_cast<size_t>(-1);
			freq = static_cast<size_t>(spaces[space_idx++]);
			free_spaces.push_back({i, freq});
		}

		for (size_t j = 0; j < freq; ++j)
		{
			row[i + j] = static_cast<int>(local_idx);
		}
		i += freq;
		is_space = !is_space;
	}

	size_t csize = chunks.size();
	std::set<Pair> seen;
	for (size_t i = 0; i < csize; ++i)
	{
		auto end_chunk = chunks[csize - i - 1];

		for (size_t j = 0; j < free_spaces.size(); ++j)
		{
			Pair free_space = free_spaces[j];

			if (seen.find(free_space) == seen.end())
			{
				if (free_space.first > end_chunk.first)
				{
					break;
				}

				if (free_space.second >= end_chunk.second)
				{
					for (size_t k = 0; k < end_chunk.second; ++k)
					{
						row[free_space.first + k] = row[end_chunk.first + k];
						row[end_chunk.first + k] = -1;
					}

					free_spaces[j].first += end_chunk.second;
					free_spaces[j].second -= end_chunk.second;

					if (free_space.second < 1)
						seen.insert(free_space);

					break;
				}
			}
		}
	}

	long long part_two = 0;
	for (size_t i = 0; i < len; ++i)
	{
		if (row[i] == -1)
			continue;

		part_two += row[i] * (int)i;
	}

	return part_two;
}

int main()
{
	std::string file_path = "./input.txt";
	std::ifstream infile(file_path);

	if (!infile.is_open())
	{
		std::cerr << "Error: Could not open the file." << std::endl;
		return 1;
	}

	char c;
	size_t idx = 0;
	size_t len = 0;
	std::vector<int> nums;
	std::vector<int> spaces;
	while (infile.get(c))
	{
		bool is_space = idx % 2 != 0;
		if (std::isdigit(c))
		{
			int num = c - '0';
			len += static_cast<size_t>(num);
			if (is_space)
			{
				spaces.push_back(num);
			}
			else
			{
				nums.push_back(num);
			}
		}
		++idx;
	}
	infile.close();

	std::cout << "Part One: " << part_one_sol(len, nums, spaces) << std::endl;
	std::cout << "Part Two: " << part_two_sol(len, nums, spaces) << std::endl;

	return 0;
}