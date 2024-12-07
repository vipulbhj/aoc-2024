#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <sstream>
#include <functional>

long long concatenate(long long num1, long long num2)
{
	if (num2 == 0)
		return num1 * 10;
	int num2Digits = static_cast<int>(std::log10(num2)) + 1;
	return num1 * static_cast<long long>(std::pow(10, num2Digits)) + num2;
}

enum class Operation
{
	ADD,
	MULTIPLY,
	CONCATENATE
};

using OperationFunc = std::function<long long(long long, long long)>;

std::pair<bool, long long> findSolution(
	const std::vector<long long> &nums,
	long long len,
	long long result,
	long long idx,
	long long acc,
	const std::vector<Operation> &allowedOps)
{
	if (idx > len)
	{
		return {false, 0};
	}

	if (len == idx)
	{
		return {result == acc, acc};
	}

	static const std::map<Operation, OperationFunc> operations = {
		{Operation::ADD, std::plus<long long>()},
		{Operation::MULTIPLY, std::multiplies<long long>()},
		{Operation::CONCATENATE, concatenate}};

	long long currentNum = nums[static_cast<std::size_t>(idx)];

	for (const auto &op : allowedOps)
	{
		auto opFunc = operations.at(op);
		auto tempResult = findSolution(
			nums,
			len,
			result,
			idx + 1,
			opFunc(acc, currentNum),
			allowedOps);

		if (tempResult.first)
		{
			return tempResult;
		}
	}

	return {false, 0};
}

int main()
{
	std::string file_path = "./sample.txt";
	std::ifstream infile(file_path);

	if (!infile.is_open())
	{
		std::cerr << "Error: Could not open the file." << std::endl;
		return 1;
	}

	const std::vector<Operation> partOneOps = {Operation::ADD, Operation::MULTIPLY};
	const std::vector<Operation> partTwoOps = {Operation::ADD, Operation::MULTIPLY, Operation::CONCATENATE};

	long long partOne = 0;
	long long partTwo = 0;

	std::string line;
	while (std::getline(infile, line))
	{
		std::stringstream ss(line);
		long long result;
		char colon;
		long long num;
		std::vector<long long> nums;

		ss >> result >> colon;
		while (ss >> num)
		{
			nums.push_back(num);
		}

		auto valid = findSolution(nums,
								  static_cast<long long>(nums.size()),
								  result,
								  1,
								  nums[0],
								  partOneOps);
		if (valid.first)
		{
			partOne += result;
		}

		auto valid_two = findSolution(nums,
									  static_cast<long long>(nums.size()),
									  result,
									  1,
									  nums[0],
									  partTwoOps);
		if (valid_two.first)
		{
			partTwo += result;
		}
	}
	infile.close();

	std::cout << "Part One: " << partOne << std::endl;
	std::cout << "Part Two: " << partTwo << std::endl;

	return 0;
}