#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>

// #define DEPTH 7
// #define WIDTH 11

#define DEPTH 103
#define WIDTH 101

struct Robot
{
	std::pair<long long, long long> pos;
	std::pair<long long, long long> vel;
};

long long partOne(std::vector<Robot> robots, long long turns)
{
	std::vector<long long> quadCount(4);

	for (long long i = 0; i < turns; ++i)
	{
		for (auto &robot : robots)
		{
			long long xPos = robot.pos.first + robot.vel.first;
			if (xPos < 0)
			{
				xPos = WIDTH + xPos;
			}
			else if (xPos >= WIDTH)
			{
				xPos = xPos - WIDTH;
			}

			long long yPos = robot.pos.second + robot.vel.second;
			if (yPos < 0)
			{
				yPos = DEPTH + yPos;
			}
			else if (yPos >= DEPTH)
			{
				yPos = yPos - DEPTH;
			}

			robot.pos.first = xPos;
			robot.pos.second = yPos;
		}
	}

	long long xMiddle = (long long)(WIDTH / 2);
	long long yMiddle = (long long)(DEPTH / 2);
	for (auto &[pos, _vel] : robots)
	{
		if (pos.first != xMiddle && pos.second != yMiddle)
		{
			if (pos.second < yMiddle)
			{
				if (pos.first < xMiddle)
				{
					quadCount[0]++;
				}
				else
				{
					quadCount[1]++;
				}
			}
			else
			{
				if (pos.first < xMiddle)
				{
					quadCount[2]++;
				}
				else
				{
					quadCount[3]++;
				}
			}
		}
	}

	long long answer = 1;
	for (const auto &pp : quadCount)
	{
		answer *= pp;
	}

	return answer;
}

long long partTwo(std::vector<Robot> robots)
{
	long long xMiddle = (long long)(WIDTH / 2);
	long long yMiddle = (long long)(DEPTH / 2);

	long long lowest = LLONG_MAX;
	long long bestTurn = 0;

	for (long long i = 0; i < 10000; ++i)
	{
		std::vector<long long> quadCount(4);
		for (auto &robot : robots)
		{
			long long xPos = robot.pos.first + robot.vel.first;
			if (xPos < 0)
			{
				xPos = WIDTH + xPos;
			}
			else if (xPos >= WIDTH)
			{
				xPos = xPos - WIDTH;
			}

			long long yPos = robot.pos.second + robot.vel.second;
			if (yPos < 0)
			{
				yPos = DEPTH + yPos;
			}
			else if (yPos >= DEPTH)
			{
				yPos = yPos - DEPTH;
			}

			robot.pos.first = xPos;
			robot.pos.second = yPos;
		}

		for (auto &[pos, _vel] : robots)
		{
			if (pos.first != xMiddle && pos.second != yMiddle)
			{
				if (pos.second < yMiddle)
				{
					if (pos.first < xMiddle)
					{
						quadCount[0]++;
					}
					else
					{
						quadCount[1]++;
					}
				}
				else
				{
					if (pos.first < xMiddle)
					{
						quadCount[2]++;
					}
					else
					{
						quadCount[3]++;
					}
				}
			}
		}

		long long sf = 1;
		for (const auto &pp : quadCount)
		{
			sf *= pp;
		}

		if (sf < lowest)
		{
			lowest = sf;
			bestTurn = i;
		}
	}

	return bestTurn + 1;
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

	std::vector<Robot> robots;

	std::string line;
	while (std::getline(infile, line))
	{
		std::stringstream ss(line);

		char c;
		std::pair<long long, long long> pos, vel;
		ss >> c >> c >> pos.first >> c >> pos.second;
		ss >> c >> c >> vel.first >> c >> vel.second;

		robots.push_back(Robot{pos, vel});
	}
	infile.close();

	std::cout << "Part One: " << partOne(robots, 100) << std::endl;
	std::cout << "Part Two: " << partTwo(robots) << std::endl;

	return 0;
}
