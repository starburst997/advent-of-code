#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <charconv>

using namespace std;

bool read_integer(const char* buffer, const int start, const int end, int& value)
{
    auto [ptr, ec]{from_chars(&buffer[start], &buffer[end], value)};
    return ec == errc();
}

void read_integers(const char* buffer, const int size, vector<int>& vector)
{
    int last_comma = 0;
    for (int i = 0; i < size; i++)
    {
        if (buffer[i] != ',') continue;
        
        if (int value; read_integer(buffer, last_comma, i, value))
            vector.push_back(value);
        
        last_comma = i + 1;
    }
    
    if (int value; read_integer(buffer, last_comma, size, value))
        vector.push_back(value);
}

int main(int argc, char* argv[])
{
    cout << "Advent of Code 2021 - Day 07" << endl << endl;

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
    const auto buffer = new char[size]{};
    stream.seekg(0, ios::beg);

    if (!stream.read(buffer, size))
    {
        cout << "Cannot read file into buffer!\n";
        return 1;
    }

    // Parse all numbers
    vector<int> crabs{};
    read_integers(buffer, size, crabs);
    delete[] buffer;
    
    // Solve the puzzle
    // I'm guessing returning the "average" (or median maybe?) would gives us a good estimate?
    sort(crabs.begin(), crabs.end());
    const int median = crabs[crabs.size() / 2];
    
    int fuel = 0;
    for (const int crab : crabs)
        fuel += abs(median - crab);
    
    cout << endl << "Answer: " << fuel << endl;
}
