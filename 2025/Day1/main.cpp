#include <cctype>
#include <cstdint>
#include <iostream>
#include <print>
#include <sys/types.h>
#include <vector>

#define __PART_2_SOLUTION 0

// Default FileIO file:
#include "../include/file_io.cpp"

using namespace std;

static uint64_t counter = 0;

class Dial {
  private:
	int8_t position;

	void _turn_left() {
		if (position == 0) {
			position = 99;
			return;
		}
		position--;
	}

	void _turn_right() {
		if (position == 99) {
			position = 0;
			return;
		}
		position++;
	}

  public:
	Dial() {
		position = 50;
	}

	void turn(char direction, int times) {
		direction = toupper(direction);

		bool wasCounted = false;

		if (direction == 'L') {
			for (ssize_t i = 0; i < times; i++) {
				_turn_left();
				if (__PART_2_SOLUTION) {
					if (position == 0) {
						counter++;
						wasCounted = true;
					}
				}
			}
		}

		if (direction == 'R') {
			for (ssize_t i = 0; i < times; i++) {
				_turn_right();
				if (__PART_2_SOLUTION) {
					if (position == 0) {
						counter++;
						wasCounted = true;
					}
				}
			}
		}

		if (position == 0) {
#if __PART_2_SOLUTION == 0
			counter++;
#else
			if (!wasCounted) {
				counter++;
			}
#endif
		}
	}
};

int main(void) {
	vector<vector<char>> input = read_char("test_case.txt");

	Dial dial = Dial();
	/* INFO: Example of input
	 * L24
	 * R13
	 */

	for (int line = 0; line < input.size() - 1; line++) {
		char direction = input[line][0];
		string number_string;

		print("Direction: [{}] ", direction);

		for (int letter = 1; letter < input[line].size(); letter++) {
			number_string.push_back(input[line][letter]);
		}

		int number = atoi(number_string.c_str());
		println("Number of times: [{}]", number);

		dial.turn(direction, number);
	}

	println("Number of times postion was 0: [{}]", counter);

	return 0;
}
