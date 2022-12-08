#include <fstream>
#include <iostream>
#include <string>

using namespace std;

enum class P1 : char
{
    Rock = 'A',
    Paper = 'B',
    Scissors = 'C',
};

enum class P2 : char
{
    Rock = 'X',
    Paper = 'Y',
    Scissors = 'Z',
};

int main(int argc, char* argv[])
{
    cout << "Advent of Code 2022 - Day 02" << endl << endl;

    string path = "Inputs.txt";
    if (argc >= 2) path = argv[1];

    ifstream stream(path);
    if (!stream)
    {
        cout << "File not found!\n";
        return 1;
    }

    int score = 0;

    string line;
    while (getline(stream, line))
    {
        cout << line << endl;

        if (line.size() < 3) continue;

        auto p1 = static_cast<P1>(line[0]);
        auto p2 = static_cast<P2>(line[2]);

        switch (p2)
        {
        case P2::Rock:
            score += 1;
            score += p1 == P1::Scissors ? 6 : p1 == P1::Rock ? 3 : 0;
            break;
        case P2::Paper:
            score += 2;
            score += p1 == P1::Rock ? 6 : p1 == P1::Paper ? 3 : 0;
            break;
        case P2::Scissors:
            score += 3;
            score += p1 == P1::Paper ? 6 : p1 == P1::Scissors ? 3 : 0;
            break;
        }
    }

    cout << endl << "Answer: " << score << endl;
    return 0;
}
