#include <fstream>
#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[])
{
    cout << "Advent of Code 2021 - Day 10 (part 2)" << endl << endl;

    string path = "Inputs.txt";
    if (argc >= 2) path = argv[1];

    ifstream stream(path);
    if (!stream)
    {
        cout << "File not found!\n";
        return 1;
    }
    
    vector<long long> lines_score{};
    
    map<char, char> chars{ {'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'} };
    map<char, int> scores{ {')', 1}, {']', 2}, {'}', 3}, {'>', 4} };
    
    string line;
    while (getline(stream, line))
    {
        cout << line << endl;

        // Find corrupted lines (wrong closing characters)
        bool error = false;
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
                // Wrong character found!
                if (c != stack.top())
                {
                    error = true;
                    break;
                }
                
                stack.pop();
            }
        }

        if (error) continue;

        // Incomplete line
        long long line_score = 0;
        while (!stack.empty())
        {
            line_score *= 5;
            line_score += scores[stack.top()];
            stack.pop();
        }

        lines_score.push_back(line_score);
    }

    sort(lines_score.begin(), lines_score.end());
    long long score = lines_score[lines_score.size() / 2];
    
    cout << endl << "Answer: " << score << endl;
}
