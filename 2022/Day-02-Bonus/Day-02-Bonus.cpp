#include <fstream>
#include <iostream>
#include <string>

using namespace std;

enum Choice : char {
	Rock = 'A',
	Paper = 'B',
	Scissors = 'C',
};

enum Condition : char {
	Lose = 'X',
	Draw = 'Y',
	Win = 'Z',
};

int main(int argc, char* argv[])
{
	cout << "Advent of Code 2022 - Day 02 (part 2)" << endl << endl;

	string path = "Inputs.txt";
	if (argc >= 2) path = argv[1];

	ifstream stream(path);
	if (!stream) {
		cout << "File not found!\n";
		return 1;
	}

	int score = 0;

	string line;
	while (getline(stream, line)) {
		cout << line << endl;

		if (line.size() < 3) continue;

		Choice p1 = Choice(line[0]);
		Choice p2 = p1;
		Condition condition = Condition(line[2]);

		// Could've used a map instead here, less lines but would it have been faster? I like the readability
		// but I would've gone with map if there was a lot more options
		switch (condition) {
		case Lose:
			score += 0;

			switch (p1) {
			case Rock:
				p2 = Scissors;
				break;
			case Paper:
				p2 = Rock;
				break;
			case Scissors:
				p2 = Paper;
				break;
			}
			break;

		case Draw:
			score += 3;
			break;

		case Win:
			score += 6;
			
			switch (p1) {
			case Rock:
				p2 = Paper;
				break;
			case Paper:
				p2 = Scissors;
				break;
			case Scissors:
				p2 = Rock;
				break;
			}
			break;
		}

		switch (p2) {
		case Rock:
			score += 1;
			break;
		case Paper:
			score += 2;
			break;
		case Scissors:
			score += 3;
			break;
		}
	}

	cout << endl << "Answer: " << score << endl;
}