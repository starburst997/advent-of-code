#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    cout << "Advent of Code 2021 - Day 09" << endl << endl;

    string path = "Inputs.txt";
    if (argc >= 2) path = argv[1];

    ifstream stream(path, ios::binary | ios::ate);
    if (!stream)
    {
        cout << "File not found!\n";
        return 1;
    }

    // Let's read the whole file buffer to memory
    const auto size = static_cast<int>(stream.tellg());
    const auto buffer = new char[size]{};
    stream.seekg(0, ios::beg);

    if (!stream.read(buffer, size))
    {
        cout << "Cannot read file into buffer!\n";
        return 1;
    }

    // Figure out how many bytes is one line
    // Windows new line are 2 chars, so check for that
    int line = 0;
    int columns = 0;
    bool new_line = false;
    for (; line < size; line++)
    {
        if (buffer[line] < '0')
            new_line = true;
        else if (new_line)
            break;
        else
            columns++;
    }

    // `+ 2` is to compensate if there isn't a new line at the end
    const int rows = (size + 2) / line;

    int total = 0;
    
    // Loop each point and figure out if it is a low point or not by checking adjacent points
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < columns; x++)
        {
            const char current = buffer[y * line + x];
            if (x > 0 && current >= buffer[y * line + x - 1]) continue;
            if (x < columns - 1 && current >= buffer[y * line + x + 1]) continue;
            if (y > 0 && current >= buffer[(y - 1) * line + x]) continue;
            if (y < rows - 1 && current >= buffer[(y + 1) * line + x]) continue;

            total += (current - '0') + 1;
        }
    }
    
    cout << endl << "Answer: " << total << endl;
}
