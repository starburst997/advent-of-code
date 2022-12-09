#include <fstream>
#include <iostream>
#include <string>
#include <charconv>
#include <vector>
#include <map>

using namespace std;

constexpr int board_size = 5;

struct position
{
    int x;
    int y;
};

// At first I saved it as an array and was looping on each possibilities
// to find the number, mark it, and again loop on marked numbers to find a bingo.
// I guess that would be the "human" algorithm, pretty inefficient...
// This was not `O(log n)`! Instead save the position of each number in a map
// Then all we need is keep a count on each lines, at 5 we have a bingo.
// Much better!
struct board
{
    map<int, position> positions;
    int horizontals[board_size];
    int verticals[board_size];

    bool skip;
    
    int total_sum;
    int marked_sum;
};

bool read_integer(const string& line, const int start, const int end, int& value)
{
    auto [ptr, ec]{from_chars(&line[start], &line[end], value)};
    return ec == errc();
}

int main(const int argc, char* argv[])
{
    cout << "Advent of Code 2021 - Day 04 (part 2)" << endl << endl;

    string path = "Inputs.txt";
    if (argc >= 2) path = argv[1];

    ifstream stream(path);
    if (!stream)
    {
        cout << "File not found!\n";
        return 1;
    }

    // Grab the numbers that were drawn
    string line;
    if (!getline(stream, line))
    {
        cout << "Empty file!\n";
        return 1;
    }

    int last_comma = 0;
    vector<int> numbers{};

    const int line_length = static_cast<int>(line.length());
    for (int i = 0; i < line_length; i++)
    {
        if (line[i] != ',') continue;
        
        if (int value; read_integer(line, last_comma, i, value))
            numbers.push_back(value);
        
        last_comma = i + 1;
    }
    
    if (int value; read_integer(line, last_comma, line_length, value))
        numbers.push_back(value);
    
    // Grab all the boards
    vector<board> boards{};
    while (getline(stream, line))
    {
        board board{};
        for (int y = 0; y < board_size; y++)
        {
            if (!getline(stream, line)) break;
            for (int x = 0; x < board_size; x++)
            {
                // 2 digit number with predictable position
                int n;
                if (line[x * 3] == ' ') n = line[x * 3 + 1] - '0';
                else n = (line[x * 3] - '0') * 10 + (line[x * 3 + 1] - '0');
                
                board.positions[n] = { x, y };
                board.total_sum += n;
            }
        }

        boards.push_back(board);
    }

    // Draw numbers
    int bingo = 0;
    auto remaining = boards.size();
    for (const int number : numbers)
    {
        for (auto& board : boards)
        {
            if (board.skip) continue;
            
            auto it = board.positions.find(number);
            if (it == board.positions.end())
                continue;

            board.marked_sum += number;
            
            // Check for bingo
            if (++board.horizontals[it->second.x] == board_size ||
                ++board.verticals[it->second.y] == board_size)
            {
                bingo = (board.total_sum - board.marked_sum) * number;
                board.skip = true;
                remaining--;
            }
        }
        
        if (remaining == 0) break;
    }
    
    cout << endl << "Answer: " << bingo << endl;
}
