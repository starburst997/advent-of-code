#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <charconv>

using namespace std;

enum direction : char
{
    unknown,
    up = 'U',
    down = 'D',
    left = 'L',
    right = 'R'
};

struct vector
{
    int x;
    int y;
};

bool read_integer(const string& line, const unsigned int start, const unsigned int end, int& value)
{
    auto [ptr, ec]{from_chars(&line[start], &line[end], value)};
    return ec == errc();
}

int main(int argc, char* argv[])
{
    cout << "Advent of Code 2022 - Day 09" << endl << endl;

    string path = "Inputs.txt";
    if (argc >= 2) path = argv[1];

    ifstream stream(path);
    if (!stream)
    {
        cout << "File not found!\n";
        return 1;
    }

    // Keep track of unique position
    int count = 1;
    map<int, bool> positions{ {0, true} };

    constexpr int max_width = 10000;
    vector head{};
    vector tail{};
    
    string line;
    while (getline(stream, line))
    {
        if (line.length() < 3) continue;

        // Read string
        const auto dir = static_cast<direction>(line[0]);

        int n = 0;
        if (!read_integer(line, 2, line.length(), n)) continue;

        // Simulate rope
        int dir_x = 0;
        int dir_y = 0;
        switch (dir)
        {
            case direction::up:
                dir_y = 1;
                break;
            case direction::down:
                dir_y = -1;
                break;
            case direction::left:
                dir_x = -1;
                break;
            case direction::right:
                dir_x = 1;
                break;
        }
        
        for (int i = 0; i < n; i++)
        {
            head.x += dir_x;
            head.y += dir_y;

            // Need to move tail?
            if (abs(head.x - tail.x) > 1 || abs(head.y - tail.y) > 1)
            {
                tail = head;
                tail.x -= dir_x;
                tail.y -= dir_y;
                
                const int id = tail.y * max_width + tail.x;
                if (positions.find(id) == positions.end())
                {
                    positions[id] = true;
                    count++;
                }
            }
        }
    }
    
    cout << endl << "Answer: " << count << endl;
    return 0;
}
