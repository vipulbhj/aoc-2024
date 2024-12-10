#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <sstream>

// #define DEPTH 8
// #define WIDTH 8

#define DEPTH 41
#define WIDTH 41

std::set<std::pair<int, int>> partOneTops;

int findTrailCount(int grid[DEPTH][WIDTH], std::set<std::pair<int, int>> visited, int row, int col, int num = 0, bool partTwo = false)
{
	if (num > 9)
		return 0;

	if (!partTwo)
	{
		if (num == 9)
		{
			if (partOneTops.find({row, col}) == partOneTops.end())
			{
				partOneTops.emplace(row, col);
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	else
	{
		if (num == 9)
			return 1;
	}

	int count = 0;

	int up = row - 1;
	int down = row + 1;
	int left = col - 1;
	int right = col + 1;

	visited.emplace(row, col);

	auto is_visited = [visited](int row, int col) -> bool
	{
		return visited.find({row, col}) != visited.end();
	};

	if (up >= 0 && up < DEPTH && grid[up][col] == num + 1 && !is_visited(up, col))
	{
		count += findTrailCount(grid, visited, up, col, num + 1, partTwo);
	}

	if (down >= 0 && down < DEPTH && grid[down][col] == num + 1 && !is_visited(down, col))
	{
		count += findTrailCount(grid, visited, down, col, num + 1, partTwo);
	}

	if (left >= 0 && left < WIDTH && grid[row][left] == num + 1 && !is_visited(row, left))
	{
		count += findTrailCount(grid, visited, row, left, num + 1, partTwo);
	}

	if (right >= 0 && right < WIDTH && grid[row][right] == num + 1 && !is_visited(row, right))
	{
		count += findTrailCount(grid, visited, row, right, num + 1, partTwo);
	}

	return count;
}

int partOneSol(const std::vector<std::pair<int, int>> &trailheads, int grid[DEPTH][WIDTH])
{
	int answer = 0;
	for (auto const &trailhead : trailheads)
	{
		partOneTops.clear();
		std::set<std::pair<int, int>> visited;
		answer += findTrailCount(grid, visited, trailhead.first, trailhead.second);
	}

	return answer;
}

int partTwoSol(const std::vector<std::pair<int, int>> &trailheads, int grid[DEPTH][WIDTH])
{
	int answer = 0;
	for (auto const &trailhead : trailheads)
	{
		partOneTops.clear();
		std::set<std::pair<int, int>> visited;
		answer += findTrailCount(grid, visited, trailhead.first, trailhead.second, 0, true);
	}

	return answer;
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

	int grid[DEPTH][WIDTH];

	int row = 0;
	std::string line;
	std::vector<std::pair<int, int>> trailheads;
	while (std::getline(infile, line))
	{
		int col = 0;
		char c = 0;
		std::stringstream ss(line);

		while (ss >> c)
		{
			int num = c - '0';

			if (num == 0)
				trailheads.push_back({row, col});

			grid[row][col++] = num;
		}
		row++;
	}
	infile.close();

	std::cout << "Part One: " << partOneSol(trailheads, grid) << std::endl;
	std::cout << "Part Two: " << partTwoSol(trailheads, grid) << std::endl;

	return 0;
}
