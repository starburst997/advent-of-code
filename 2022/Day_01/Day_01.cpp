#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    cout << "Advent of Code 2022 - Day 01" << endl << endl;

    string path = "Inputs.txt";
    if (argc >= 2) path = argv[1];

    ifstream stream(path);
    if (!stream)
    {
        cout << "File not found!\n";
        return 1;
    }

    int max = 0;
    int count = 0;

    string line;
    while (getline(stream, line))
    {
        cout << line << endl;

        if (line.empty())
        {
            if (count > max) max = count;
            count = 0;
            continue;
        }

        try
        {
            count += stoi(line);
        }
        catch (...)
        {
            // Skip
        }
    }

    if (count > max) max = count;

    cout << endl << "Answer: " << max << endl;
}
