#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(const int argc, char* argv[])
{
    cout << "Advent of Code 2022 - Day 08 (part 2)" << endl << endl;

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

    // No need to check the outer layer
    int score = 0;
    for (int x = 1; x < columns - 1; x++)
    {
        for (int y = 1; y < rows - 1; y++)
        {
            const char c = buffer[y * line + x];
            
            // Check left
            int left = 0;
            for (int i = x - 1; i >= 0; i--)
            {
                left++;
                if (buffer[y * line + i] >= c) break;
            }
            
            // Check right
            int right = 0;
            for (int i = x + 1; i < columns; i++)
            {
                right++;
                if (buffer[y * line + i] >= c) break;
            }
            
            // Check top
            int top = 0;
            for (int i = y - 1; i >= 0; i--)
            {
                top++;
                if (buffer[i * line + x] >= c)  break;
               
            }

            // Check bottom
            int bottom = 0;
            for (int i = y + 1; i < rows; i++)
            {
                bottom++;
                if (buffer[i * line + x] >= c) break;
            }

            const int local_score = left * right * top * bottom;
            if (local_score > score) score = local_score;
        }
    }
    
    delete[] buffer;
    
    cout << endl << "Answer: " << score << endl;
    return 0;
}
