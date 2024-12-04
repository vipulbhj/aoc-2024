#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <sstream>

int LINE_WIDTH = -1;
int LINE_COUNT = 0;
std::vector<char> characters;

using Indexes = std::array<int, 4>;

int is_xmas(const std::vector<char> &chars, Indexes idxs)
{
	size_t i = (size_t)idxs[0], j = (size_t)idxs[1], k = (size_t)idxs[2], l = (size_t)idxs[3];
	return (chars[i] == 'X' && chars[j] == 'M' && chars[k] == 'A' && chars[l] == 'S');
}

int is_samx(const std::vector<char> &chars, Indexes idxs)
{
	size_t i = (size_t)idxs[0], j = (size_t)idxs[1], k = (size_t)idxs[2], l = (size_t)idxs[3];
	return (chars[i] == 'S' && chars[j] == 'A' && chars[k] == 'M' && chars[l] == 'X');
}

int is_mas_pattern(const std::vector<char> &chars, Indexes idxs)
{
	size_t i = (size_t)idxs[0], j = (size_t)idxs[1], k = (size_t)idxs[2], l = (size_t)idxs[3];
	return (chars[i] == 'M' && chars[j] == 'S' && chars[k] == 'M' && chars[l] == 'S') ||
		   (chars[i] == 'S' && chars[j] == 'M' && chars[k] == 'S' && chars[l] == 'M') ||
		   (chars[i] == 'S' && chars[j] == 'S' && chars[k] == 'M' && chars[l] == 'M') ||
		   (chars[i] == 'M' && chars[j] == 'M' && chars[k] == 'S' && chars[l] == 'S');
}

Indexes row(int startIdx)
{
	int startRow = startIdx / LINE_WIDTH;
	int endIdx = startIdx + 3;
	int endRow = endIdx / LINE_WIDTH;

	if (startRow == endRow && endIdx < LINE_COUNT * LINE_WIDTH)
	{
		return {
			startIdx,
			startIdx + 1,
			startIdx + 2,
			startIdx + 3};
	}
	return {
		-1,
		-1,
		-1,
		-1};
}

Indexes col(int startIdx)
{
	int endIdx = startIdx + 3 * LINE_WIDTH;
	if (endIdx < LINE_COUNT * LINE_WIDTH)
	{
		return {
			startIdx,
			startIdx + LINE_WIDTH,
			startIdx + 2 * LINE_WIDTH,
			startIdx + 3 * LINE_WIDTH};
	}
	return {
		-1,
		-1,
		-1,
		-1};
}

Indexes leftDiagonal(int startIdx)
{
	int startRow = startIdx / LINE_WIDTH;
	int startCol = startIdx % LINE_WIDTH;
	int endRow = (startIdx + 3 * (LINE_WIDTH + 1)) / LINE_WIDTH;
	int endCol = (startCol + 3) % LINE_WIDTH;

	if ((endRow - startRow) == 3 &&
		endCol > startCol &&
		(startIdx + 3 * (LINE_WIDTH + 1)) < LINE_COUNT * LINE_WIDTH)
	{
		return {
			startIdx,
			startIdx + (LINE_WIDTH + 1),
			startIdx + 2 * (LINE_WIDTH + 1),
			startIdx + 3 * (LINE_WIDTH + 1)};
	}
	return {
		-1,
		-1,
		-1,
		-1};
}

Indexes rightDiagonal(int startIdx)
{
	int startRow = startIdx / LINE_WIDTH;
	int startCol = startIdx % LINE_WIDTH;
	int endRow = (startIdx + 3 * (LINE_WIDTH - 1)) / LINE_WIDTH;
	int endCol = (startCol - 3 + LINE_WIDTH) % LINE_WIDTH;

	if ((endRow - startRow) == 3 &&
		endCol < startCol &&
		startCol >= 3 &&
		(startIdx + 3 * (LINE_WIDTH - 1)) < LINE_COUNT * LINE_WIDTH)
	{
		return {
			startIdx,
			startIdx + (LINE_WIDTH - 1),
			startIdx + 2 * (LINE_WIDTH - 1),
			startIdx + 3 * (LINE_WIDTH - 1)};
	}
	return {
		-1,
		-1,
		-1,
		-1};
}

bool is_valid(Indexes idxs)
{
	int i = idxs[0], j = idxs[1], k = idxs[2], l = idxs[3];
	return i != -1 && j != -1 && k != -1 && l != -1;
}

Indexes masPattern(int startIdx)
{
	int topM = startIdx - LINE_WIDTH - 1;
	int topS = startIdx - LINE_WIDTH + 1;
	int bottomM = startIdx + LINE_WIDTH - 1;
	int bottomS = startIdx + LINE_WIDTH + 1;

	if (topM >= 0 && topS >= 0 &&
		bottomM < LINE_COUNT * LINE_WIDTH &&
		bottomS < LINE_COUNT * LINE_WIDTH &&
		topM / LINE_WIDTH == (topS / LINE_WIDTH) &&
		startIdx / LINE_WIDTH == ((topM / LINE_WIDTH) + 1) &&
		bottomM / LINE_WIDTH == bottomS / LINE_WIDTH &&
		startIdx / LINE_WIDTH == ((bottomM / LINE_WIDTH) - 1))
	{
		return {
			topM,
			topS,
			bottomM,
			bottomS};
	}

	return {
		-1,
		-1,
		-1,
		-1};
}

void partOne()
{
	int partOneCount = 0;

	int total = LINE_WIDTH * LINE_COUNT;
	for (int i = 0; i < total; ++i)
	{
		Indexes r = row(i);
		Indexes c = col(i);
		Indexes ld = leftDiagonal(i);
		Indexes rd = rightDiagonal(i);

		if (is_valid(r))
		{
			if (is_xmas(characters, r) || is_samx(characters, r))
			{
				++partOneCount;
			}
		}

		if (is_valid(c))
		{
			if (is_xmas(characters, c) || is_samx(characters, c))
			{
				++partOneCount;
			}
		}

		if (is_valid(ld))
		{
			if (is_xmas(characters, ld) || is_samx(characters, ld))
			{
				++partOneCount;
			}
		}

		if (is_valid(rd))
		{
			if (is_xmas(characters, rd) || is_samx(characters, rd))
			{
				++partOneCount;
			}
		}
	}

	std::cout << "Part One: " << partOneCount << std::endl;
}

void partTwo()
{
	int partTwoCount = 0;
	int total = LINE_WIDTH * LINE_COUNT;
	for (int i = 0; i < total; ++i)
	{
		if (characters[(size_t)i] != 'A')
			continue;
		Indexes idxs = masPattern(i);
		if (is_valid(idxs) && is_mas_pattern(characters, idxs))
		{
			++partTwoCount;
		}
	}

	std::cout << "Part Two: " << partTwoCount << std::endl;
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

	std::string line;
	while (std::getline(infile, line))
	{
		LINE_WIDTH = (int)line.length();
		++LINE_COUNT;
		for (char c : line)
		{
			characters.push_back(c);
		}
	}
	infile.close();

	partOne();
	partTwo();

	return 0;
}
