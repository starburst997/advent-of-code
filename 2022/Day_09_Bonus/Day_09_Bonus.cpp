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
    cout << "Advent of Code 2022 - Day 09 (part 2)" << endl << endl;

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
    constexpr int knots = 10;
    
    vector rope[knots]{};
    vector& head = rope[0];
    
    string line;
    while (getline(stream, line))
    {
        if (line.length() < 3) continue;

        // Read string
        const auto dir = static_cast<direction>(line[0]);

        int n = 0;
        if (!read_integer(line, 2, line.length(), n)) continue;

        // Simulate rope
        vector movement{};
        switch (dir)
        {
            case direction::up:
                movement.y = 1;
                break;
            case direction::down:
                movement.y = -1;
                break;
            case direction::left:
                movement.x = -1;
                break;
            case direction::right:
                movement.x = 1;
                break;
        }
        
        for (int i = 0; i < n; i++)
        {
            head.x += movement.x;
            head.y += movement.y;

            for (int j = 1; j < knots; j++)
            {
                // Need to move knot?
                const vector& previous = rope[j - 1];
                vector& current = rope[j];

                const int diff_x = previous.x - current.x;
                const int diff_y = previous.y - current.y;
                if (abs(diff_x) <= 1 && abs(diff_y) <= 1)
                    break;
                
                // Pretty happy to have figure this one out, I think this is the simplest way to achieve this?
                // The rope "physics" wasn't at all what I expected at first
                // Will need to check other people's solution to compare
                if (diff_x != 0) current.x += diff_x / abs(diff_x);
                if (diff_y != 0) current.y += diff_y / abs(diff_y);
                
                // Only count the tail
                if (j != knots - 1) continue;
                
                const int id = current.y * max_width + current.x;
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
