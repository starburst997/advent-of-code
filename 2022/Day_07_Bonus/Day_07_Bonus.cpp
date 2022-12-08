#include <fstream>
#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

enum instruction
{
    unknown,
    change_directory,
    list
};

struct command
{
    instruction instruction;
    string value;
};

bool parse_command(const string& line, command& command)
{
    if (line.rfind("cd", 2) == 2)
    {
        command.instruction = change_directory;
        command.value = line.substr(5, line.length() - 5);
    }
    else if (line.rfind("ls", 2) == 2)
    {
        command.instruction = list;
    }

    return true;
}

int main(const int argc, char* argv[])
{
    cout << "Advent of Code 2022 - Day 07 (part 2)" << endl << endl;

    string path = "Inputs.txt";
    if (argc >= 2) path = argv[1];

    ifstream stream(path);
    if (!stream)
    {
        cout << "File not found!\n";
        return 1;
    }

    int size = 0;
    command command;
    string line;

    stack<int> current_size{};
    vector<int> sizes{};
    while (getline(stream, line))
    {
        if (line[0] == '$')
        {
            if (parse_command(line, command))
            {
                switch (command.instruction)
                {
                    case change_directory:
                        if (command.value == "..")
                        {
                            // We're finished with this folder
                            sizes.push_back(size);

                            size += current_size.top();
                            current_size.pop();
                        }
                        else
                        {
                            current_size.push(size);
                            size = 0;
                        }
                        break;
                    case list:
                        break;
                }
            }

            continue;
        }

        // Parse file from `ls`
        // Since the line start with an integer, this should works
        if (line[0] >= '0' && line[0] <= '9')
            size += stoi(line);
    }

    // Pop back to beginning
    while (!current_size.empty())
    {
        sizes.push_back(size);

        size += current_size.top();
        current_size.pop();
    }

    // Find folder to delete
    const int unused = 70000000 - size;
    const int missing = 30000000 - unused;

    int smallest = INT_MAX;
    for (int size : sizes)
    {
        if (size > missing && size < smallest) smallest = size;
    }
    
    cout << endl << "Answer: " << smallest << endl;
    return 0;
}
