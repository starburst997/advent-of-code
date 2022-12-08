#include <fstream>
#include <iostream>
#include <string>
#include <charconv>

using namespace std;

struct elf
{
    int start;
    int end;
};

bool read_integer(const string& line, const int start, const int end, int& value)
{
    auto [ptr, ec]{from_chars(&line[start], &line[end], value)};
    return ec == errc();
}

bool read_pair(ifstream& stream, elf& elf1, elf& elf2)
{
    string line;
    if (!getline(stream, line)) return false;

    // Elf1
    const auto split = line.find(',');
    if (split == string::npos) return false;

    auto range = line.find('-');
    if (range == string::npos) return false;

    if (!read_integer(line, 0, range, elf1.start)) return false;
    if (!read_integer(line, range + 1, split, elf1.end)) return false;

    // Elf2
    range = line.find('-', split + 1);
    if (range == string::npos) return false;

    if (!read_integer(line, split + 1, range, elf2.start)) return false;
    if (!read_integer(line, range + 1, line.length(), elf2.end)) return false;

    return true;
}

bool in_between(elf a, elf b)
{
    return (a.start >= b.start && a.start <= b.end) ||
        (a.end >= b.start && a.end <= b.end);
}

int main(int argc, char* argv[])
{
    cout << "Advent of Code 2022 - Day 04 (part 2)" << endl << endl;

    string path = "Inputs.txt";
    if (argc >= 2) path = argv[1];

    ifstream stream(path);
    if (!stream)
    {
        cout << "File not found!\n";
        return 1;
    }

    int count = 0;

    elf elf1, elf2;
    while (read_pair(stream, elf1, elf2))
    {
        cout << "Elf1: " << elf1.start << " / " << elf1.end << endl;
        cout << "Elf2: " << elf2.start << " / " << elf2.end << endl << endl;

        if (in_between(elf1, elf2) || in_between(elf2, elf1))
        {
            count++;
        }
    }

    cout << endl << "Answer: " << count << endl;
    return 0;
}
