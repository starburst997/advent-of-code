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
    cout << "Advent of Code 2022 - Day 10" << endl << endl;

    string path = "Inputs.txt";
    if (argc >= 2) path = argv[1];

    ifstream stream(path);
    if (!stream)
    {
        cout << "File not found!\n";
        return 1;
    }

    int total = 0;
    int register_x = 1;

    int cycles = 0;
    int cycle_check = 20;

    string line;
    while (getline(stream, line))
    {
        int pending_addx = 0;
        const instruction instruction = line[0] == 'a' ? addx : noop;
        switch (instruction)
        {
            case noop:
                // Sleep 1 cycle
                cycles += 1;
                break;
            case addx:
                // Add number to register x
                int n;
                if (!read_integer(line, 5, line.length(), n)) continue;

                pending_addx = n;
                cycles += 2;
                break;
        }

        if (cycles >= cycle_check)
        {
            total += register_x * cycle_check;

            if ((cycle_check += 40) > 220) cycle_check = INT_MAX;
        }

        register_x += pending_addx;
    }

    cout << endl << "Answer: " << total << endl;
    return 0;
}
