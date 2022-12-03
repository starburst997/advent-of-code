#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
	cout << "Advent of Code 2021 - Day 03" << endl << endl;

	string path = "Inputs.txt";
	if (argc >= 2) path = argv[1];

	ifstream stream(path);
	if (!stream) {
		cout << "File not found!\n";
		return 1;
	}

	string line;
	if (!getline(stream, line)) {
		cout << "Empty file!\n";
		return 1;
	}

	int count = line.size();
	int* counter = new int[count] { };

	int total = 0;
	do {
		cout << line << endl;

		if (line.size() < count) continue;

		for (int i = 0; i < count; i++) {
			if (line[i] == '1') counter[i]++;
		}

		total++;
	} while (getline(stream, line));

	int gamma = 0;
	for (int i = 0; i < count; i++) {
		if (counter[i] > total / 2) gamma |= (1 << (count - i - 1));
	}

	delete[] counter;

	int epsilon = (~gamma) & ((1 << count) - 1);

	cout << endl << gamma << " | " << epsilon << endl;

	cout << endl << "Answer: " << (gamma * epsilon) << endl;
}