#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>

using Number = unsigned long long;

struct pair_hash
{
	template <class T1, class T2>
	std::size_t operator()(const std::pair<T1, T2> &pair) const
	{
		return std::hash<T1>()(pair.first) ^ (std::hash<T2>()(pair.second) << 1);
	}
};

std::unordered_map<Number, Number> NUM_DIGIT;
std::unordered_map<std::pair<Number, Number>, Number, pair_hash> CACHE;

Number numDigits(Number number)
{
	if (NUM_DIGIT.find(number) != NUM_DIGIT.end())
		return NUM_DIGIT[number];

	Number original_number = number;
	Number digits = 0;
	while (number > 0)
	{
		number /= 10;
		digits++;
	}
	NUM_DIGIT[original_number] = digits;
	return digits;
}

Number build_power_of_ten(Number exp)
{
	Number result = 1;
	while (exp--)
		result *= 10;
	return result;
}

Number count_stones(Number stone, Number blinks)
{
	if (blinks == 0)
		return 1;

	if (CACHE.find({stone, blinks}) != CACHE.end())
		return CACHE[{stone, blinks}];

	if (stone == 0)
	{
		Number val = count_stones(1, blinks - 1);
		CACHE[{stone, blinks}] = val;
		return val;
	}

	Number digits = numDigits(stone);

	if (digits % 2 == 1)
	{
		Number val = count_stones(stone * 2024, blinks - 1);
		CACHE[{stone, blinks}] = val;
		return val;
	}

	Number half = digits / 2;
	Number factor = build_power_of_ten(half);
	Number left = stone / factor;
	Number right = stone % factor;

	Number valL = count_stones(left, blinks - 1);
	Number valR = count_stones(right, blinks - 1);

	CACHE[{stone, blinks}] = valL + valR;
	return valL + valR;
}

Number parts_sol(const std::vector<Number> &input, Number blinks)
{
	Number total = 0;
	for (const auto &n : input)
	{
		total += count_stones(n, blinks);
	}
	return total;
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
	std::vector<Number> items;
	while (std::getline(infile, line))
	{
		std::stringstream ss(line);
		Number n;
		while (ss >> n)
		{
			items.push_back(n);
		}
	}
	infile.close();

	std::cout << "Part One: " << parts_sol(items, 25) << std::endl;
	std::cout << "Part Two: " << parts_sol(items, 75) << std::endl;

	return 0;
}