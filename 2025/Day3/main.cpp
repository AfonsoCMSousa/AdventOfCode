#include <algorithm>
#include <cctype>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include <vector>

#define __PART_2_SOLUTION 0

// Default FileIO file:
#include "../include/file_io.cpp"

using namespace std;

vector<uint64_t> get_all_combinations_sorted(vector<uint64_t> _vec) {
	vector<uint64_t> _combinations;

	for (int _first_pos = 0; _first_pos < _vec.size(); _first_pos++) {
		for (int _second_pos = _first_pos + 1; _second_pos < _vec.size(); _second_pos++) {
			_combinations.push_back((_vec[_first_pos] * 10) + _vec[_second_pos]);
		}
	}

	sort(_combinations.begin(), _combinations.end());

	return _combinations;
}

uint32_t get_max_output_joltage(vector<uint64_t> _vec) {
	uint32_t max;
	bool _found_biggest = false;

	auto combinations = get_all_combinations_sorted(_vec);
	max = combinations[combinations.size() - 1];

	printf("Max: %u\n", max);

	return max;
}

int main(void) {
	vector<vector<char>> lables = read_char("./test_case.txt");
	uint32_t total_joltage = 0;

	for (vector<char> lable : lables) {
		if (lable.empty())
			continue;

		vector<uint64_t> _digits;
		for (char c : lable) {
			if (isdigit(c)) {
				_digits.push_back(c - '0'); // Convert char '5' to int 5
			}
		}

		total_joltage += get_max_output_joltage(_digits);
	}
	printf("\n");

	printf("Total Joltage: %u\n", total_joltage);

	return 0;
}
