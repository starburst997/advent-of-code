#include <fstream>
#include <iostream>
#include <string>
#include <map>

using namespace std;

int main(int argc, char* argv[])
{
	cout << "Advent of Code 2022 - Day 03 (part 2)" << endl << endl;

	string path = "Inputs.txt";
	if (argc >= 2) path = argv[1];

	ifstream stream(path);
	if (!stream)
	{
		cout << "File not found!\n";
		return 1;
	}

	int sum = 0;
	int counter = 0;

	string line;
	map<char, int> compartment = {};
	while (getline(stream, line))
	{
		cout << endl << line << endl;

		// Add first half to a map
		const int total = line.length() / 2;
		for (int i = 0; i < total; i++)
		{
			compartment[line[i]] = 1;
		}

		// Check if char exists in map
		for (int i = total; i < line.length(); i++)
		{
			char c = line[i];
			if (compartment.find(c) != compartment.end())
			{
				cout << "Found " << c << endl;

				sum += c <= 'Z' ? (c - 'A' + 27) : (c - 'a' + 1);
				break;
			}
		}

		if (((++counter) % 3) == 0)
		{
			compartment.clear();
		}
	}

	cout << endl << "Answer: " << sum << endl;
}
