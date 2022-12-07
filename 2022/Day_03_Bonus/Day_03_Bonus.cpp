#include <fstream>
#include <iostream>
#include <string>
#include <map>

using namespace std;

int main(int argc, char* argv[])
{
    cout << "Advent of Code 2022 - Day 03 (part 2)" << endl << endl;

    string path = "Inputs.txt";
    if (argc >= 2) path = argv[1];

    ifstream stream(path);
    if (!stream)
    {
        cout << "File not found!\n";
        return 1;
    }

    int sum = 0;

    string line;
    map<char, int> compartment = {};
    while (getline(stream, line))
    {
        compartment.clear();

        // Add first line
        for (char& i : line) compartment[i] = 1;

        // Second line
        if (!getline(stream, line)) break;
        for (char& i : line)
        {
            auto it = compartment.find(i);
            if (it != compartment.end())
            {
                // Mark as found on second line
                it->second = 2;
            }
        }

        // Third line
        if (!getline(stream, line)) break;
        for (char& i : line)
        {
            auto it = compartment.find(i);
            if (it != compartment.end())
            {
                if (it->second == 2)
                {
                    // Found it!
                    sum += i <= 'Z' ? (i - 'A' + 27) : (i - 'a' + 1);
                    break;
                }
            }
        }
    }

    cout << endl << "Answer: " << sum << endl;
}
