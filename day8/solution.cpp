#include <set>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

// #define WIDTH 10
// #define DEPTH 10

// #define WIDTH 12
// #define DEPTH 12

#define WIDTH 50
#define DEPTH 50

char GRID[DEPTH][WIDTH];

int part_one_solution(std::unordered_map<char, std::vector<std::pair<int, int>>> const &antennas)
{
	std::set<std::pair<int, int>> seen;
	for (const auto &antenna : antennas)
	{
		const auto &towers = antenna.second;
		for (size_t i = 0; i < towers.size() - 1; ++i)
		{
			for (size_t j = i + 1; j < towers.size(); ++j)
			{
				int row_diff = static_cast<int>(std::abs(towers[i].first - towers[j].first));
				int col_diff = static_cast<int>(std::abs(towers[i].second - towers[j].second));

				int coord_one_x, coord_one_y, coord_two_x, coord_two_y;

				if (towers[i].second > towers[j].second)
				{
					coord_two_y = towers[i].second + col_diff;
					coord_one_y = towers[j].second - col_diff;
				}
				else
				{
					coord_two_y = towers[i].second - col_diff;
					coord_one_y = towers[j].second + col_diff;
				}

				if (towers[i].first > towers[j].first)
				{
					coord_two_x = towers[i].first + row_diff;
					coord_one_x = towers[j].first - row_diff;
				}
				else
				{
					coord_two_x = towers[i].first - row_diff;
					coord_one_x = towers[j].first + row_diff;
				}

				if (coord_one_x > -1 && coord_one_x < DEPTH && coord_one_y > -1 && coord_one_y < WIDTH)
				{
					seen.insert({coord_one_x, coord_one_y});
				}
				if (coord_two_x > -1 && coord_two_x < DEPTH && coord_two_y > -1 && coord_two_y < WIDTH)
				{
					seen.insert({coord_two_x, coord_two_y});
				}
			}
		}
	}

	return static_cast<int>(seen.size());
}

int part_two_solution(std::unordered_map<char, std::vector<std::pair<int, int>>> const &antennas)
{
	int count = 0;
	std::set<std::pair<int, int>> seen;
	for (const auto &antenna : antennas)
	{
		const auto &towers = antenna.second;
		count += static_cast<int>(towers.size());
		for (size_t i = 0; i < towers.size(); ++i)
		{
			for (size_t j = 0; j < towers.size(); ++j)
			{
				if (i != j)
				{
					int row_diff = static_cast<int>(std::abs(towers[i].first - towers[j].first));
					int col_diff = static_cast<int>(std::abs(towers[i].second - towers[j].second));

					bool down = (towers[j].first - towers[i].first) > 0;
					bool right = (towers[j].second - towers[i].second) > 0;

					std::pair<int, int> node = towers[j];

					int coord_x, coord_y;
					while (true)
					{
						if (down)
						{
							coord_y = node.first + row_diff;
						}
						else
						{
							coord_y = node.first - row_diff;
						}

						if (right)
						{
							coord_x = node.second + col_diff;
						}
						else
						{
							coord_x = node.second - col_diff;
						}

						if (coord_x > -1 && coord_x < DEPTH && coord_y > -1 && coord_y < WIDTH)
						{

							if (GRID[coord_y][coord_x] == '.')
								seen.insert({coord_y, coord_x});
							node = {coord_y, coord_x};
						}
						else
						{
							break;
						}
					}
				}
			}
		}
	}

	return static_cast<int>(seen.size()) + count;
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

	int row = 0;
	std::string line;
	std::unordered_map<char, std::vector<std::pair<int, int>>> antennas;
	while (std::getline(infile, line))
	{
		int col = 0;
		std::stringstream ss(line);
		char c;
		while (ss >> c)
		{
			GRID[row][col] = c;
			if (c != '.')
			{
				antennas[c].push_back({row, col});
			}
			++col;
		}
		++row;
	}
	infile.close();

	// int part_one = part_one_solution(antennas);
	int part_two = part_two_solution(antennas);

	// std::cout << "Part One: " << part_one << std::endl;
	std::cout << "Part Two: " << part_two << std::endl;

	return 0;
}