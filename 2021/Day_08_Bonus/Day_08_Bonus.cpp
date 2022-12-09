#include <fstream>
#include <iostream>
#include <string>
#include <map>

using namespace std;

int bitwise(const char c, map<char, char>& cypher)
{
    return 1 << (cypher[c] - 'a');
}

void add_reference(const string& line, const int start, const int end, string (&references)[10], map<char, int>& counter)
{
    const int count = end - start;
    switch (count)
    {
        case 2: // 1
            references[1] = line.substr(start, count);
            break;
        case 4: // 4
            references[4] = line.substr(start, count);
            break;
        case 3: // 7
            references[7] = line.substr(start, count);
            break;
        case 7: // 8
            references[8] = line.substr(start, count);
            break;
    }

    // Read each chars to keep a count
    for (int i = start; i < end; i++)
        counter[line[i]]++;
}

void decode(const string& line, const int start, const int end, map<char, char>& cypher, int& number, const int decimal, map<int, int>& dictionary)
{
    int n = 0;

    const int count = end - start;
    switch (count)
    {
        // Unique numbers
        case 2: // 1
            n = 1;
            break;
        case 4: // 4
            n = 4;
            break;
        case 3: // 7
            n = 7;
            break;
        case 7: // 8
            n = 8;
            break;

        // Unknown
        case 5: // 2, 3, 5
        case 6: // 0, 6, 9
            // Create the bitwise unique number and get the current #
            for (int i = start; i < end; i++)
                n |= 1 << (line[i] - 'a');
        
            n = dictionary[n];
            break;
    }

    // Add decimal
    number += static_cast<int>(pow(10, decimal)) * n;
}

int main(int argc, char* argv[])
{
    cout << "Advent of Code 2021 - Day 08 (part 2)" << endl << endl;

    string path = "Inputs.txt";
    if (argc >= 2) path = argv[1];

    ifstream stream(path);
    if (!stream)
    {
        cout << "File not found!\n";
        return 1;
    }

    constexpr char delimiter_output = '|';
    constexpr char delimiter_digit = ' ';

    int total = 0;

    // Reference:
    // 0 = 6
    // 1* = 2
    // 2 = 5
    // 3 = 5
    // 4* = 4
    // 5 = 5
    // 6 = 6
    // 7* = 3
    // 8* = 7
    // 9 = 6

    // There is 3 letter we can figure out with simple counting (b = 6, e = 4, f = 9)
    // a = 8
    // b* = 6
    // c = 8
    // d = 7
    // e* = 4
    // f* = 9
    // g = 7

    // I'm guessing that with only the "unique' number we can deduce the rest
    // So find all unique number and save them to be processed afterward
    string line;
    string reference[10]{};   // Some unused space, but should be more efficient than a map
    map<char, char> cypher{}; // Was using an array before but it's harder to read, performance hit is minimal
    map<char, int> counter{};
    map<int, int> dictionary{};
    
    while (getline(stream, line))
    {
        for (char i = 'a'; i <= 'g'; i++) // Reset
        {
            counter[i] = 0;
            cypher[i] = '?';
        }
           
        const auto index = line.find(delimiter_output);
        const int size = static_cast<int>(line.size());
        int last_digit = 0;

        // Find all reference numbers, only care about the "unique" number
        for (int i = 0; i < index - 1; i++)
        {
            if (line[i] != delimiter_digit) continue;
            
            add_reference(line, last_digit, i, reference, counter);
            last_digit = i + 1;
        }
        
        add_reference(line, last_digit, index - 1, reference, counter);

        // Not sure if there is some magic algo so I'm using some deduction
        // I'll have to compare with others solutions to see...
        // I think my solution is still "fast" in the sense it isn't doing too much operations but I wonder if there
        // was something simpler...
        
        // First there is letter we can for sure tell from their frequency
        for (char i = 'a'; i <= 'g'; i++)
        {
            switch (counter[i])
            {
                case 6:
                    cypher['b'] = i;
                    break;
                case 4:
                    cypher['e'] = i;
                    break;
                case 9:
                    cypher['f'] = i;
                    break;
            }
        }
        
        // Now with the unique numbers, we can make some deduction
        // We know `f` so we can deduce `c` from `1`
        string num_str = reference[1];
        for (int i = 0; i < 2; i++)
        {
            // Here, I'm looping because I think the order is scrambled? Otherwise we could've just check the "position" directly
            const char c = num_str[i];
            if (c == cypher['f']) continue;

            cypher['c'] = c;
            break;
        }

        // We know `c`, `f`, so we can figure out `a` from `7`
        num_str = reference[7];
        for (int i = 0; i < 3; i++)
        {
            const char c = num_str[i];
            if (c == cypher['f'] || c == cypher['c']) continue;

            cypher['a'] = c;
            break;
        }

        // We know `b`, `c`, `f`, so we can figure out `d` from `4`
        num_str = reference[4];
        for (int i = 0; i < 4; i++)
        {
            const char c = num_str[i];
            if (c == cypher['f'] || c == cypher['c'] || c == cypher['b']) continue;

            cypher['d'] = c;
            break;
        }

        // Now we know, a, b, c, d, e, f, so the last unknown letter must be g
        num_str = reference[8];
        for (int i = 0; i < 7; i++)
        {
            const char c = num_str[i];
            if (c == cypher['a'] || c == cypher['b'] || c == cypher['c'] ||
                c == cypher['d'] || c == cypher['e'] || c == cypher['f'])
                continue;

            cypher['g'] = c;
            break;
        }

        // Now using bitwise op, create a unique number from the cypher for each number so we can look them up efficiently
        // I'm doing this because everything is scrambled (I think?) and wanted to skip looping over and over
        dictionary.clear();

        // Maybe I could skip this and do it once? (Without the cypher) 
        dictionary[
            bitwise('a', cypher) |
            bitwise('b', cypher) |
            bitwise('c', cypher) |
            bitwise('e', cypher) |
            bitwise('f', cypher) |
            bitwise('g', cypher)
        ] = 0;

        dictionary[
            bitwise('c', cypher) |
            bitwise('f', cypher)
        ] = 1;

        dictionary[
            bitwise('a', cypher) |
            bitwise('c', cypher) |
            bitwise('d', cypher) |
            bitwise('e', cypher) |
            bitwise('g', cypher)
        ] = 2;

        dictionary[
            bitwise('a', cypher) |
            bitwise('c', cypher) |
            bitwise('d', cypher) |
            bitwise('f', cypher) |
            bitwise('g', cypher)
        ] = 3;

        dictionary[
            bitwise('b', cypher) |
            bitwise('c', cypher) |
            bitwise('d', cypher) |
            bitwise('f', cypher)
        ] = 4;

        dictionary[
            bitwise('a', cypher) |
            bitwise('b', cypher) |
            bitwise('d', cypher) |
            bitwise('f', cypher) |
            bitwise('g', cypher)
        ] = 5;

        dictionary[
            bitwise('a', cypher) |
            bitwise('b', cypher) |
            bitwise('d', cypher) |
            bitwise('e', cypher) |
            bitwise('f', cypher) |
            bitwise('g', cypher)
        ] = 6;

        dictionary[
            bitwise('a', cypher) |
            bitwise('c', cypher) |
            bitwise('f', cypher)
        ] = 7;

        dictionary[
            bitwise('a', cypher) |
            bitwise('b', cypher) |
            bitwise('c', cypher) |
            bitwise('d', cypher) |
            bitwise('e', cypher) |
            bitwise('f', cypher) |
            bitwise('g', cypher)
        ] = 8;

        dictionary[
            bitwise('a', cypher) |
            bitwise('b', cypher) |
            bitwise('c', cypher) |
            bitwise('d', cypher) |
            bitwise('f', cypher) |
            bitwise('g', cypher)
        ] = 9;
        
        // We can then proceed to decode the numbers
        int decimal = 4;
        int number = 0;
        last_digit = static_cast<int>(index + 2);
        for (int i = last_digit; i < size; i++)
        {
            const char c = line[i];
            if (c != delimiter_digit) continue;

            decode(line, last_digit, i, cypher, number, --decimal, dictionary);
            last_digit = i + 1;
        }

        decode(line, last_digit, size, cypher, number, --decimal, dictionary);

        total += number;
    }

    cout << endl << "Answer: " << total << endl;
}
