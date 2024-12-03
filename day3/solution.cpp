#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>

int main() {
    std::string file_path = "./input.txt";
    std::ifstream infile(file_path);

    if (!infile.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return 1;
    }

    std::string program((std::istreambuf_iterator<char>(infile)),
                        std::istreambuf_iterator<char>());

    std::regex mult("mul\\((\\d{1,3}),(\\d{1,3})\\)|don\\'t|do");

    auto begin = std::sregex_iterator(program.begin(), program.end(), mult);
    auto end = std::sregex_iterator();

    bool doMult = true;
    int partOne = 0;
    int partTwo = 0;

    if (begin != end) {
        for (auto it = begin; it != end; ++it) {
            std::smatch match = *it;
            
            if(match.str() != "don't" && match.str() != "do") {
                int first = std::stoi(match[1]);
                int second = std::stoi(match[2]);
                partOne += first * second;
                if(doMult) partTwo += first*second;
            } else if(match.str() == "don't") {
                doMult = false;
            } else if(match.str() == "do") {
                doMult = true;
            }
        }
    }

    std::cout << "Part One: " << partOne << std::endl;
    std::cout << "Part Two: " << partTwo << std::endl;

    return 0;
}
