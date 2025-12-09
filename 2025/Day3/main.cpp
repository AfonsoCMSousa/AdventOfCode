#include <algorithm>
#include <cctype>
#include <cstdint>
#include <cstdio>
#include <format>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include <vector>

#define __PART_2_SOLUTION 1
const uint64_t max_digitis = 12;

// Default FileIO file:
#include "../include/file_io.cpp"

using namespace std;

vector<uint64_t> get_all_combinations_sorted(vector<uint64_t> _vec) {

	vector<uint64_t> _combinations;
#if __PART_2_SOLUTION == 0

	for (int _first_pos = 0; _first_pos < _vec.size(); _first_pos++) {
		for (int _second_pos = _first_pos + 1; _second_pos < _vec.size(); _second_pos++) {
			_combinations.push_back((_vec[_first_pos] * 10) + _vec[_second_pos]);
		}
	}

	sort(_combinations.begin(), _combinations.end());

	return _combinations;
#else
	int32_t _max_drop = _vec.size() - max_digitis;
	vector<uint64_t> _max;

	if (_max_drop <= 0) {
		throw runtime_error(format("No avaiable solution because _max_drop ({}) < _vec.size() ({})", _max_drop, _vec.size()));
	}

	for (int i = 0; i < _vec.size(); i++) {

		while (!_max.empty() && _max_drop > 0 && _max.back() < _vec[i]) {
			_max.pop_back();
			_max_drop--;
		}
		_max.push_back(_vec[i]);
	}

	string res;
	for (int d : _max_drop > 0 ? vector<uint64_t>(_max.begin(), _max.end() - _max_drop) : _max)
		res.push_back('0' + d);

	// Debug: Print result
	printf("Resulting max digits: %s\n", res.c_str());

	_combinations.push_back(stoul(res));
#endif
	return _combinations;
}

uint64_t get_max_output_joltage(vector<uint64_t> _vec) {
	uint64_t max;

	auto combinations = get_all_combinations_sorted(_vec);

	// Debug: Print all _combinations
	if (combinations.size() == 0) {
		return 0;
	}

	printf("Combinations: ");
	for (uint64_t comb : combinations) {
		printf("%lu ", comb);
	}
	printf("\n");

	max = combinations[combinations.size() - 1];

	printf("Max: %lu\n", max);

	return max;
}

int main(void) {
	vector<vector<char>> lables = read_char("./test_case.txt");
	uint64_t total_joltage = 0;

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

	printf("Total Joltage: %lu\n", total_joltage);

	return 0;
}
