#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct grid
{
    char* buffer;
    int line; // How many char per line
    
    int columns;
    int rows;
};

// TODO: Replace with a better flood fill algorithm https://en.wikipedia.org/wiki/Flood_fill also benchmark them, I'll curious to see how my "naive" approach compares...
bool mark_and_count(const grid& grid, const int start_x, const int start_y, int& count, const bool check_x = true, const bool check_y = true)
{
    char& current = grid.buffer[start_y * grid.line + start_x];
    if (current == '9') return false;
    
    count++;
    current = '9';

    // Look in each direction and start the func again
    // Will have to check how other people did it, not sure if this is optimal...
    // It should be pretty fast tho since I'm not going over any char that I've parsed
    if (check_x)
    {
        for (int x = start_x - 1; x >= 0; x--) // Left
        {
            if (!mark_and_count(grid, x, start_y, count, false, true))
                break;
        }

        for (int x = start_x + 1; x < grid.columns; x++) // Right
        {
            if (!mark_and_count(grid, x, start_y, count, false, true))
                break;
        }
    }

    if (check_y)
    {
        for (int y = start_y - 1; y >= 0; y--) // Up
        {
            if (!mark_and_count(grid, start_x, y, count, true, false))
                break;
        }

        for (int y = start_y + 1; y < grid.rows; y++) // Down
        {
            if (!mark_and_count(grid, start_x, y, count, true, false))
                break;
        }
    }
    
    return true;
}

int main(int argc, char* argv[])
{
    cout << "Advent of Code 2021 - Day 09 (part 2)" << endl << endl;

    string path = "Inputs.txt";
    if (argc >= 2) path = argv[1];

    ifstream stream(path, ios::binary | ios::ate);
    if (!stream)
    {
        cout << "File not found!\n";
        return 1;
    }

    // Let's read the whole file buffer to memory
    const auto size = static_cast<int>(stream.tellg());
    
    grid grid{ new char[size]{}, 0, 0, 0 };
    stream.seekg(0, ios::beg);

    if (!stream.read(grid.buffer, size))
    {
        cout << "Cannot read file into buffer!\n";
        return 1;
    }

    // Figure out how many bytes is one line
    // Windows new line are 2 chars, so check for that
    bool new_line = false;
    for (; grid.line < size; grid.line++)
    {
        if (grid.buffer[grid.line] < '0')
            new_line = true;
        else if (new_line)
            break;
        else
            grid.columns++;
    }

    // `+ 2` is to compensate if there isn't a new line at the end
    grid.rows = (size + 2) / grid.line;
    vector<int> sizes{};
    
    // Loop each point, any char except 9 is part of a basin
    // Mark traveled point as '9' so we don't check them again
    for (int y = 0; y < grid.rows; y++)
    {
        for (int x = 0; x < grid.columns; x++)
        {
            const char current = grid.buffer[y * grid.line + x];
            if (current == '9') continue;

            // Start counting every characters in the basin with a recursive func
            int counter = 0;
            mark_and_count(grid, x, y, counter);
            
            sizes.push_back(counter);
        }
    }

    // Multiply the last 3 elements in the set
    sort(sizes.begin(), sizes.end(), greater{});
    const int total = sizes[0] * sizes[1] * sizes[2];
    
    cout << endl << "Answer: " << total << endl;
}
