#include <fstream>
#include <iostream>
#include <string>
#include <stack>
#include <map>

using namespace std;

int main(int argc, char* argv[])
{
    cout << "Advent of Code 2021 - Day 10" << endl << endl;

    string path = "Inputs.txt";
    if (argc >= 2) path = argv[1];

    ifstream stream(path);
    if (!stream)
    {
        cout << "File not found!\n";
        return 1;
    }

    int score = 0;
    map<char, char> chars{ {'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'} };
    map<char, int> scores{ {')', 3}, {']', 57}, {'}', 1197}, {'>', 25137} };
    
    string line;
    while (getline(stream, line))
    {
        cout << line << endl;

        // Find corrupted lines (wrong closing characters)
        stack<char> stack{};
        for (const char c : line)
        {

            auto it = chars.find(c);
            if (it != chars.end())
            {
                stack.push(it->second);
            }
            else
            {
                if (c != stack.top())
                {
                    // Wrong character found!
                    score += scores[c];
                    break;
                }
                
                stack.pop();
            }
        }
    }

    cout << endl << "Answer: " << score << endl;
}
