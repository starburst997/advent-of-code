#include <fstream>
#include <iostream>
#include <string>
#include <map>

using namespace std;

int main(const int argc, char* argv[])
{
    cout << "Advent of Code 2022 - Day 06 (part 2)" << endl << endl;

    string path = "Inputs.txt";
    if (argc >= 2) path = argv[1];

    ifstream stream(path);
    if (!stream)
    {
        cout << "File not found!\n";
        return 1;
    }

    string line;
    constexpr int lookup = 14;
    if (!getline(stream, line) || line.length() < lookup)
    {
        cout << "Empty file!\n";
        return 1;
    }

    // As we progress thru the stream, keep count in a hashmap and number of unique chars
    map<char, int> map{};
    for (char i = 'a'; i <= 'z'; i++) map[i] = 0;

    int unique = 0;
    for (int i = 0; i < lookup; i++) // Init first N chars
    {
        if (map[line[i]]++ == 0) unique++;
    }

    if (unique == lookup) // Early exit
    {
        cout << "Answer: " << lookup << endl;
        return 0;
    }

    // Process one char at a time
    int first_marker = 0;
    for (int i = lookup; i < line.length(); i++)
    {
        if (--map[line[i - lookup]] == 0) unique--;

        if (map[line[i]]++ == 0)
        {
            if (++unique == lookup)
            {
                first_marker = i + 1;
                break;
            }
        }
    }

    cout << "Answer: " << first_marker << endl;
    return 0;
}
