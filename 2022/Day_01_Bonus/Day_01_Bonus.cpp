#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void AddToMax(int count, int max[], int offset, int length) 
{
	for (int i = offset; i < length; i++) {
		if (count > max[i]) {
			int previous = max[i];
			max[i] = count;

			AddToMax(previous, max, offset, length);
			break;
		}
	}
}

int main(int argc, char* argv[])
{
	cout << "Advent of Code 2022 - Day 01 (part 2)" << endl << endl;

	string path = "Inputs.txt";
	if (argc >= 2) path = argv[1];

	ifstream stream(path);
	if (!stream) {
		cout << "File not found!\n";
		return 1;
	}

	const int TOP = 3;
	int max[TOP] = { };

	int count = 0;

	string line;
	while (getline(stream, line)) {
		cout << line << endl;

		if (line.empty()) {
			AddToMax(count, max, 0, TOP);
			count = 0;
			continue;
		}

		try {
			count += stoi(line);
		}
		catch (...) {
			// Skip
		}
	}

	AddToMax(count, max, 0, TOP);

	cout << endl << "Top 3:" << endl << endl;

	count = 0;
	for (int i = 0; i < TOP; i++) {
		count += max[i];

		cout << max[i] << endl;
	}

	cout << endl << "Answer: " << count << endl;
}