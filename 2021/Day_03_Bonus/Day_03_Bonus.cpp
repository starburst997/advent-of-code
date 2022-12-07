#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int FindValue(vector<int> numbers, int count, bool searchOne = true)
{
    vector<int> temp = {};

    for (int i = count - 1; i >= 0; i--)
    {
        // Most common bit
        int count = 0;
        int total = numbers.size();
        for (int j = 0; j < total; j++)
        {
            if ((numbers[j] & (1 << i)) != 0)
                count++;
        }

        bool oneMostly = count >= total / 2.0f;
        if (!searchOne) oneMostly = !oneMostly;

        cout << count << " / " << total << " (" << oneMostly << ")" << endl;

        // Keep numbers if contains bit
        for (int j = 0; j < total; j++)
        {
            int value = numbers[j];
            if ((value & (1 << i)) != 0)
            {
                if (oneMostly) temp.push_back(value);
            }
            else
            {
                if (!oneMostly) temp.push_back(value);
            }
        }

        numbers = temp;
        if (numbers.size() == 1)
        {
            return numbers[0];
        }

        temp.clear();
    }

    return 0;
}

int main(int argc, char* argv[])
{
    cout << "Advent of Code 2021 - Day 03 (part 2)" << endl << endl;

    string path = "Inputs.txt";
    if (argc >= 2) path = argv[1];

    ifstream stream(path);
    if (!stream)
    {
        cout << "File not found!\n";
        return 1;
    }

    string line;
    if (!getline(stream, line))
    {
        cout << "Empty file!\n";
        return 1;
    }

    int count = line.size();

    vector<int> numbers = {};
    do
    {
        cout << line << endl;

        if (line.size() < count) continue;

        int number = 0;
        for (int i = 0; i < count; i++)
        {
            if (line[i] == '1')
            {
                number |= (1 << (count - i - 1));
            }
        }

        numbers.push_back(number);
    }
    while (getline(stream, line));

    cout << endl;

    int oxygen = FindValue(numbers, count);
    cout << oxygen << endl << endl;

    int co2 = FindValue(numbers, count, false);
    cout << co2 << endl;

    cout << endl << "Answer: " << (oxygen * co2) << endl;
}
