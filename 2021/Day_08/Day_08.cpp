#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void increment_total(const int count, int& total)
{
    if (count == 2 || count == 4 || count == 3 || count == 7)
        total++;
}

int main(int argc, char* argv[])
{
    cout << "Advent of Code 2021 - Day 08" << endl << endl;

    string path = "Inputs.txt";
    if (argc >= 2) path = argv[1];

    ifstream stream(path);
    if (!stream)
    {
        cout << "File not found!\n";
        return 1;
    }

    constexpr char delimiter_output = '|';
    constexpr char delimiter_digit = ' ';

    int total = 0;

    string line;
    while (getline(stream, line))
    {
        const auto index = line.find(delimiter_output);
        if (index == string::npos) continue;

        int last_digit = static_cast<int>(index + 2);
        const int size = static_cast<int>(line.size());
        for (int i = last_digit; i < size; i++)
        {
            const char c = line[i];
            if (c != delimiter_digit) continue;

            increment_total(i - last_digit, total);
            last_digit = i + 1;
        }

        increment_total(size - last_digit, total);
    }
    
    cout << endl << "Answer: " << total << endl;
}
