#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    cout << "Advent of Code 2021 - Day 01" << endl << endl;

    string path = "Inputs.txt";
    if (argc >= 2) path = argv[1];

    ifstream stream(path);
    if (!stream)
    {
        cout << "File not found!\n";
        return 1;
    }

    int increased = 0;
    int value = 0;
    int previous = -1;

    string line;
    while (getline(stream, line))
    {
        cout << line << endl;

        try
        {
            value = stoi(line);
            if (value > previous && previous >= 0) increased++;
            previous = value;
        }
        catch (...)
        {
            // Skip
        }
    }

    cout << endl << "Answer: " << increased << endl;
}
