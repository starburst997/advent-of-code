#include <fstream>
#include <iostream>
#include <string>
#include <charconv>
#include <vector>

using namespace std;

const string arrow_delimiter = " -> ";
constexpr char comma_delimiter = ',';

struct point
{
    int x;
    int y;
};

struct line
{
    point start;
    point end;
};

bool read_integer(const string& line, const int start, const int end, int& value)
{
    auto [ptr, ec]{from_chars(&line[start], &line[end], value)};
    return ec == errc();
}

int main(const int argc, char* argv[])
{
    cout << "Advent of Code 2021 - Day 05" << endl << endl;

    string path = "Inputs.txt";
    if (argc >= 2) path = argv[1];

    ifstream stream(path);
    if (!stream)
    {
        cout << "File not found!\n";
        return 1;
    }

    // Parse all lines points
    string line_str;

    vector<line> lines{};
    int max_x = 0, max_y = 0;
    while (getline(stream, line_str))
    {
        const auto arrow_index = line_str.find(arrow_delimiter);
        if (arrow_index == string::npos) continue;

        line line{};

        // Start
        auto index = line_str.find(comma_delimiter);
        if (index == string::npos) continue;

        if (!read_integer(line_str, 0, index, line.start.x)) continue;
        if (!read_integer(line_str, index + 1, arrow_index, line.start.y)) continue;

        // End
        index = line_str.find(comma_delimiter, arrow_index + arrow_delimiter.length());
        if (index == string::npos) continue;

        if (!read_integer(line_str, arrow_index + arrow_delimiter.length(), index, line.end.x)) continue;
        if (!read_integer(line_str, index + 1, line_str.length(), line.end.y)) continue;

        // Check max grid size
        if (line.start.x > max_x) max_x = line.start.x;
        if (line.end.x > max_x) max_x = line.end.x;

        if (line.start.y > max_y) max_y = line.start.y;
        if (line.end.y > max_y) max_y = line.end.y;
        
        lines.push_back(line);
    }
    
    max_x++;
    max_y++;
    
    // Debug lines output
    /*for (const auto& line : lines)
    {
        cout << "Start: " << line.start.x << ", " << line.start.y << " End: " << line.end.x << ", " << line.end.y << endl;
    }*/

    // Since this is a "grid" (int pt), I guess we can simply "draw" the line on it and keep track of how many "intersect"
    // Otherwise we loop on each lines and then need to loop again on all of them for intersection which would grow the complexity to `O(2^n)`
    // Maybe there is another clever solution I'm not seeing...
    int count = 0;
    const auto grid = new int[max_y * max_x]{};
    for (const auto& line : lines)
    {
        const int diff_x = abs(line.end.x - line.start.x);
        const int diff_y = abs(line.end.y - line.start.y);
        const int length = diff_x > diff_y ? diff_x : diff_y;

        const point direction = {
            line.start.x < line.end.x ? 1 : line.start.x > line.end.x ? -1 : 0,
            line.start.y < line.end.y ? 1 : line.start.y > line.end.y ? -1 : 0
        };

        int x = line.start.x;
        int y = line.start.y;
        for (int i = 0; i <= length; i++)
        {
            if (++grid[y * max_x + x] == 2) count++;

            x += direction.x;
            y += direction.y;
        }
    }

    // Debug grid output
    /*for (int y = 0; y < max_y; y++)
    {
        for (int x = 0; x < max_x; x++)
        {
            cout << grid[y * max_y + x];
        }
        
        cout << endl;
    }*/

    delete[] grid;

    cout << endl << endl << "Answer: " << count << endl;
}
