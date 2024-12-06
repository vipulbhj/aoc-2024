#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <sstream>

// #define WIDTH 10
// #define DEPTH 10

#define WIDTH 130
#define DEPTH 130

int main()
{
	std::string file_path = "./input.txt";
	std::ifstream infile(file_path);

	int lab[DEPTH][WIDTH] = {};
	int x = -1, y = -1;

	if (!infile.is_open())
	{
		std::cerr << "Error: Could not open the file." << std::endl;
		return 1;
	}

	int i = 0;
	std::string line;
	while (std::getline(infile, line))
	{
		std::stringstream ss(line);
		char c;

		int j = 0;
		while (ss >> c)
		{
			if (c == '#')
			{
				lab[i][j] = 1;
			}
			else if (c == '^')
			{
				x = i;
				y = j;
			}
			++j;
		}
		++i;
	}
	infile.close();

	int start_x = x;
	int start_y = y;
	std::vector<std::pair<int, int>> possibilities;

	int direction = 1;
	int partOneCount = 0;

	while (x > -1 && x < DEPTH && y > -1 && y < WIDTH)
	{
		if (direction == 1)
		{
			// Moving up till we see a blocker
			if (x - 1 < 0)
			{
				possibilities.push_back(std::make_pair(x, y));
				++partOneCount;
				break;
			}
			if (lab[x - 1][y] == 1)
			{
				direction = 2;
			}
			else
			{
				if (lab[x][y] != -1)
				{
					lab[x][y] = -1;
					++partOneCount;
					possibilities.push_back(std::make_pair(x, y));
				}

				x -= 1;
			}
		}
		else if (direction == 2)
		{
			// Moving right till we see a blocker
			if (y + 1 >= WIDTH)
			{
				possibilities.push_back(std::make_pair(x, y));
				++partOneCount;
				break;
			}
			if (lab[x][y + 1] == 1)
			{
				direction = 3;
			}
			else
			{
				if (lab[x][y] != -1)
				{
					lab[x][y] = -1;
					++partOneCount;
					possibilities.push_back(std::make_pair(x, y));
				}
				y += 1;
			}
		}
		else if (direction == 3)
		{
			// Moving down till we see a blocker
			if (x + 1 >= DEPTH)
			{
				possibilities.push_back(std::make_pair(x, y));
				++partOneCount;
				break;
			}
			if (lab[x + 1][y] == 1)
			{
				direction = 4;
			}
			else
			{
				if (lab[x][y] != -1)
				{
					lab[x][y] = -1;
					++partOneCount;
					possibilities.push_back(std::make_pair(x, y));
				}
				x += 1;
			}
		}
		else if (direction == 4)
		{
			// Moving left till we see a blocker
			if (y - 1 < 0)
			{
				possibilities.push_back(std::make_pair(x, y));
				++partOneCount;
				break;
			}
			if (lab[x][y - 1] == 1)
			{
				direction = 1;
			}
			else
			{
				if (lab[x][y] != -1)
				{
					lab[x][y] = -1;
					++partOneCount;
					possibilities.push_back(std::make_pair(x, y));
				}
				y -= 1;
			}
		}
	}

	int partTwoCount = 0;
	for (const auto &it : possibilities)
	{
		x = start_x;
		y = start_y;
		direction = 1;

		// SKIP PLACING AT THE STARTING POSITION
		if ((start_x == it.first && start_y == it.second))
			continue;

		int step = 0;
		while (x > -1 && x < DEPTH && y > -1 && y < WIDTH)
		{
			if (direction == 1)
			{
				// Moving up till we see a blocker
				if (x - 1 < 0)
					break;

				if (lab[x - 1][y] == 1 || (x - 1 == it.first && y == it.second))
					direction = 2;
				else
					x -= 1;
			}
			else if (direction == 2)
			{
				// Moving right till we see a blocker
				if (y + 1 >= WIDTH)
					break;

				if (lab[x][y + 1] == 1 || (x == it.first && y + 1 == it.second))
					direction = 3;
				else
					y += 1;
			}
			else if (direction == 3)
			{
				// Moving down till we see a blocker
				if (x + 1 >= DEPTH)
					break;

				if (lab[x + 1][y] == 1 || (x + 1 == it.first && y == it.second))
					direction = 4;
				else
					x += 1;
			}
			else if (direction == 4)
			{
				// Moving left till we see a blocker
				if (y - 1 < 0)
					break;

				if (lab[x][y - 1] == 1 || (x == it.first && y - 1 == it.second))
					direction = 1;
				else
					y -= 1;
			}

			++step;
			if (step > WIDTH * DEPTH)
			{
				// LOOP
				++partTwoCount;
				break;
			}
		}
	}

	std::cout << "Part One: " << partOneCount << std::endl;
	std::cout << "Part Two: " << partTwoCount << std::endl;

	return 0;
}
