#include <fstream>
#include <iostream>
#include <string>
#include <charconv>
#include <deque>
#include <stack>

using namespace std;

struct instruction
{
    int quantity;
    int position;
    int destination;
};

bool read_integer(const string& line, const int start, const int end, int& value)
{
    auto [ptr, ec]{from_chars(&line[start], &line[end], value)};
    return ec == errc();
}

bool read_word(const string& line, int& offset, int& value)
{
    auto start = line.find(' ', offset);
    if (start == string::npos) return false;

    auto end = line.find(' ', start + 1);
    if (end == string::npos) end = line.length();

    if (!read_integer(line, start + 1, end, value)) return false;

    offset = end + 1;
    return true;
}

bool read_instruction(ifstream& stream, instruction& move)
{
    string line;
    if (!getline(stream, line)) return false;

    int offset = 0;
    if (!read_word(line, offset, move.quantity)) return false;
    if (!read_word(line, offset, move.position)) return false;
    if (!read_word(line, offset, move.destination)) return false;

    return true;
}

int main(const int argc, char* argv[])
{
    cout << "Advent of Code 2022 - Day 05  (part 2)" << endl << endl;

    string path = "Inputs.txt";
    if (argc >= 2) path = argv[1];

    ifstream stream(path);
    if (!stream)
    {
        cout << "File not found!\n";
        return 1;
    }

    // Read crates
    string line;

    getline(stream, line);

    const int count = (line.length() + 1) / 4;
    const auto crates = new deque<char>[count]{};

    do
    {
        if (line.length() < 2 || (line[1] >= '0' && line[1] <= '9')) break;

        for (int i = 0; i < count; i++)
        {
            char c = line[i * 4 + 1];
            if (c == ' ') continue;

            crates[i].push_front(c);
        }
    }
    while (getline(stream, line));

    // Empty line
    getline(stream, line);

    // Parse instruction
    instruction instruction;
    stack<char> temp;
    while (read_instruction(stream, instruction))
    {
        auto& from = crates[instruction.position - 1];
        auto& destination = crates[instruction.destination - 1];

        const int total = from.size() < instruction.quantity ? from.size() : instruction.quantity;

        for (int i = 0; i < total; i++)
        {
            temp.push(from.back());
            from.pop_back();
        }

        for (int i = 0; i < total; i++)
        {
            destination.push_back(temp.top());
            temp.pop();
        }
    }

    // Show answer
    cout << endl << "Answer: ";

    for (int i = 0; i < count; i++)
    {
        auto& crate = crates[i];

        if (crate.empty()) cout << ' ';
        else cout << crate.back();
    }

    delete[] crates;

    cout << endl;
    return 0;
}
