#include <fstream>
#include <iostream>
#include <string>

using namespace std;

enum Direction
{
    Forward,
    Down,
    Up
};

bool ReadLine(ifstream& stream, Direction& direction, int& value)
{
    string line;
    if (!getline(stream, line)) return false;

    const char DELIMITER = ' ';
    int index = line.find(DELIMITER);
    if (index == string::npos) return false;

    try
    {
        if (line.compare(0, index, "forward") == 0) direction = Forward;
        else if (line.compare(0, index, "down") == 0) direction = Down;
        else if (line.compare(0, index, "up") == 0) direction = Up;

        // Integer is always one char so we can speed things up
        //string partB = line.substr(index + 1, line.size() - index - 1);
        //value = stoi(partB);

        value = line[index + 1] - '0';
    }
    catch (...)
    {
        return false;
    }

    return true;
}

int main(int argc, char* argv[])
{
    cout << "Advent of Code 2021 - Day 02 (part 2)" << endl << endl;

    string path = "Inputs.txt";
    if (argc >= 2) path = argv[1];

    ifstream stream(path);
    if (!stream)
    {
        cout << "File not found!\n";
        return 1;
    }

    Direction direction;
    int value = 0, position = 0, depth = 0, aim = 0;

    while (ReadLine(stream, direction, value))
    {
        cout << direction << " | " << value << endl;

        switch (direction)
        {
        case Forward:
            position += value;
            depth += aim * value;
            break;
        case Down:
            aim += value;
            break;
        case Up:
            aim -= value;
            break;
        }
    }

    cout << endl << "Answer: " << (depth * position) << endl;
}
