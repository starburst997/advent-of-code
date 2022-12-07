#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool ReadLineInt(ifstream& stream, int& value) {
	string line;
	if (!getline(stream, line)) return false;

	try {
		value = stoi(line);
	}
	catch (...) {
		return false;
	}

	return true;
}

int main(int argc, char* argv[])
{
	cout << "Advent of Code 2021 - Day 01 (part 2)" << endl << endl;

	string path = "Inputs.txt";
	if (argc >= 2) path = argv[1];

	ifstream stream(path);
	if (!stream) {
		cout << "File not found!\n";
		return 1;
	}

	const int WINDOW = 3;
	int previous[WINDOW] = { };

	int increased = 0;
	int counter = WINDOW;

	int value, valueA = 0, valueB = 0;
	for (int i = 0; i < WINDOW; i++) {
		ReadLineInt(stream, previous[i]);
		valueA += previous[i];
	}

	while (ReadLineInt(stream, value)) {
		cout << value << endl;

		// Remove previous first value and add new value
		int index = (counter++) % WINDOW;
		valueB = valueA - previous[index] + value;

		previous[index] = value;

		if (valueB > valueA) increased++;
		valueA = valueB;

		cout << valueA << " | " << valueB << endl;
	}

	cout << endl << "Answer: " << increased << endl;
}