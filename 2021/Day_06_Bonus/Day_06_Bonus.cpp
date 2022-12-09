#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

constexpr int days = 256;

int main(const int argc, char* argv[])
{
    cout << "Advent of Code 2021 - Day 06 (part 2)" << endl << endl;

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

    // Process each numbers
    const int count = (size + 1) / 2;
    map<int, long long> map{ {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0} };
    for (int i = 0; i < count; i++)
    {
        int n = buffer[i * 2] - '0';
        map[n]++;
    }
    
    delete[] buffer;

    // Simulate birth (kind of a brute force approach... Need to revisit it...)
    // Way too slow for 256!!
    /*for (int day = 0; day < days; day++)
    {
        for (int i = 0, total = fishes.size(); i < total; i++)
        {
            if (fishes[i]-- == 0)
            {
                fishes[i] = 6;
                fishes.push_back(8);
            }
        }
    }*/

    // Hate to admit it but I lost a bunch of time trying to optimize it figuring a "formula" a la `2^(d / 7)`
    // I'm sure some mathematician could figure one out... But turns out it was much simpler
    
    // More optimized version with a map keeping track of each fish with the same age
    // Basically move down the counter as each days pass, every fish with a time of 5 will become 4, etc.
    // no need to decrement each of them manually, only the "group". When a group reach zero they
    // get added to the sixth position.
    for (int i = 0; i < days; i++)
    {
        /*const auto zero = map[0];
        for (int j = 0; j < 8; j++)
            map[j] = map[j + 1];

        map[8] = zero;
        map[6] = zero + map[6];*/
        
        // Slightly more optimized version than above that does the same thing but without needing to copy down
        map[(i + 7) % 9] += map[i % 9];
    }
    
    long long total = 0;
    for (auto const& [key, val] : map)
        total += val;
    
    cout << endl << endl << "Answer: " << total << endl;
}
