#include <fstream>
#include <iostream>
#include <string>
#include <charconv>

using namespace std;

enum instruction
{
    noop,
    addx
};

bool read_integer(const string& line, const unsigned int start, const unsigned int end, int& value)
{
    auto [ptr, ec]{from_chars(&line[start], &line[end], value)};
    return ec == errc();
}


int main(int argc, char* argv[])
{
    cout << "Advent of Code 2022 - Day 10 (part 2)" << endl << endl;

    string path = "Inputs.txt";
    if (argc >= 2) path = argv[1];

    ifstream stream(path);
    if (!stream)
    {
        cout << "File not found!\n";
        return 1;
    }

    int register_x = 1;

    int cycles = 0;

    constexpr int width = 40;
    constexpr int height = 6;

    int x = 0;
    char crt[width * height]{};
    
    string line;
    while (getline(stream, line))
    {
        int duration = 1;
        int pending_addx = 0;
        const instruction instruction = line[0] == 'a' ? addx : noop;
        switch (instruction)
        {
            case noop:
                // Sleep 1 cycle
                break;
            case addx:
                // Add number to register x
                int n = 0;
                read_integer(line, 5, line.length(), n);
                
                pending_addx = n;
                duration = 2;
                break;
        }

        for (int i = 0; i < duration; i++)
        {
            // Do we have a sprite on the current drawing position?
            crt[cycles] = x >= register_x - 1 && x <= register_x + 1 ? '#' : '.';

            cycles++;
            if (++x >= width) x = 0;
        }

        register_x += pending_addx;
    }

    // Draw CRT
    cout << endl << "Answer: " << endl << endl;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++) cout << crt[y * width + x];
        cout << endl;
    }

    cout << endl << endl;

    return 0;
}
