#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <sstream>

using Number = unsigned long long;

Number part_one(Number X, Number Y, Number XX, Number YY, Number Z, Number ZZ)
{
	Number numerator = (Number)std::abs(static_cast<long long>(ZZ * XX - YY * Z));
	Number denominator = (Number)std::abs(static_cast<long long>(XX * Y - X * YY));

	if (numerator % denominator != 0)
		return 0;

	Number A = numerator / denominator;

	numerator = (Number)std::abs(static_cast<long long>(Z - X * A));
	denominator = XX;

	if (numerator % denominator != 0)
		return 0;

	Number B = numerator / denominator;

	if (A < 101 && B < 101)
	{
		return A * 3 + B;
	}
	else
	{
		return 0;
	}
}

Number part_two(Number X, Number Y, Number XX, Number YY, Number Z, Number ZZ)
{
	Number factor = 10000000000000;
	Z += factor;
	ZZ += factor;

	Number numerator = (Number)std::abs(static_cast<long long>(ZZ * XX - YY * Z));
	Number denominator = (Number)std::abs(static_cast<long long>(XX * Y - X * YY));

	if (numerator % denominator != 0)
		return 0;

	Number A = numerator / denominator;

	numerator = (Number)std::abs(static_cast<long long>(Z - X * A));
	denominator = XX;

	if (numerator % denominator != 0)
		return 0;

	Number B = numerator / denominator;

	return A * 3 + B;
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

	std::vector<std::tuple<Number, Number, Number, Number, Number, Number>> games;

	std::string line;
	std::vector<Number> temp;
	while (std::getline(infile, line))
	{

		std::stringstream ss(line);

		if (line == "")
		{
			games.push_back(std::make_tuple(temp[0], temp[1], temp[2], temp[3], temp[4], temp[5]));
			temp.clear();
		}

		char c;
		while (ss >> c)
		{
			if (c == '+' || c == '=')
			{
				Number n;
				ss >> n;
				temp.push_back(n);
			}
		}
	}
	games.push_back(std::make_tuple(temp[0], temp[1], temp[2], temp[3], temp[4], temp[5]));
	temp.clear();

	Number part_one_answer = 0;
	Number part_two_answer = 0;
	for (const auto &game : games)
	{
		part_one_answer += part_one(
			std::get<0>(game),
			std::get<1>(game),
			std::get<2>(game),
			std::get<3>(game),
			std::get<4>(game),
			std::get<5>(game));

		part_two_answer += part_two(
			std::get<0>(game),
			std::get<1>(game),
			std::get<2>(game),
			std::get<3>(game),
			std::get<4>(game),
			std::get<5>(game));
	}

	std::cout << "Part One: " << part_one_answer << std::endl;
	std::cout << "Part Two: " << part_two_answer << std::endl;

	return 0;
}
