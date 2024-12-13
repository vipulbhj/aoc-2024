#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_set>

#define DEPTH 140
#define WIDTH 140

char GRID[DEPTH][WIDTH];
bool VISITED[DEPTH][WIDTH];

std::vector<std::pair<int, int>> DIRECTIONS{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

bool inside_grid(int row, int col)
{
    return 0 <= row && row < DEPTH && 0 <= col && col < WIDTH;
}

void dfs(int row, int col, int &area, int &perimeter)
{
    VISITED[row][col] = true;
    area++;
    for (const auto &[x, y] : DIRECTIONS)
    {
        int r = row + x;
        int c = col + y;

        if (!inside_grid(r, c) || GRID[r][c] != GRID[row][col])
        {
            perimeter++;
        }
        else if (!VISITED[r][c])
        {
            dfs(r, c, area, perimeter);
        }
    }
}

void dfsPartTwo(int row, int col, int &area, int &sides)
{
    VISITED[row][col] = true;
    area++;

    auto good = [&](std::pair<int, int> direction)
    {
        int r = row + direction.first;
        int c = col + direction.second;

        return inside_grid(r, c) && GRID[r][c] == GRID[row][col];
    };

    for (std::size_t i = 0; i < 4; ++i)
    {
        auto d = DIRECTIONS[i];
        auto dd = DIRECTIONS[(i + 1) % 4];

        if (!good(d) && !good(dd))
        {
            sides++;
        }

        if (good(d) && good(dd) && !good({d.first + dd.first, d.second + dd.second}))
        {
            sides++;
        }
    }

    for (const auto &[x, y] : DIRECTIONS)
    {
        int r = row + x;
        int c = col + y;

        if (good({x, y}) && !VISITED[r][c])
        {
            dfsPartTwo(r, c, area, sides);
        }
    }
}

int main()
{
    std::string file_path = "./input.txt";
    std::fstream infile(file_path);

    int i = 0;
    std::string line;
    while (std::getline(infile, line))
    {
        int j = 0;
        std::stringstream ss(line);
        char c;
        while (ss >> c)
            GRID[i][j++] = c;
        ++i;
    }

    int partOne = 0;
    for (int row = 0; row < DEPTH; ++row)
    {
        for (int col = 0; col < WIDTH; ++col)
        {
            if (!VISITED[row][col])
            {
                int area = 0, perimeter = 0;
                dfs(row, col, area, perimeter);
                partOne += area * perimeter;
            }
        }
    }

    memset(VISITED, false, sizeof GRID);

    int partTwo = 0;
    for (int row = 0; row < DEPTH; ++row)
    {
        for (int col = 0; col < WIDTH; ++col)
        {
            if (!VISITED[row][col])
            {
                int area = 0, sides = 0;
                dfsPartTwo(row, col, area, sides);
                partTwo += area * sides;
            }
        }
    }

    std::cout << "Part One: " << partOne << std::endl;
    std::cout << "Part Two: " << partTwo << std::endl;
}