#include <algorithm>
#include <cctype>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <vector>

#define __PART_2_SOLUTION 1

// Default FileIO file:
#include "../include/file_io.cpp"

using namespace std;

typedef struct {
	uint_fast64_t min;
	uint_fast64_t max;
} interval;

bool is_multiple_of(uint64_t number, uint64_t multiple) {
    return (number % multiple) == 0;
}

// NOTE: Esta até deixa o prof. Marco orgolhoso
uint64_t cauculuate_invalid_ids_in_interval(interval inter) {
	uint64_t invalids = 0;

	for (uint64_t i = inter.min; i <= inter.max; i++) {
		vector<uint64_t> _digitis = get_digits(i);


		string _first_half, _second_half;
		for (int _j = _digitis.size() - 1; _j >= 0; _j--) {
			if (_j >= _digitis.size() / 2) {
				_second_half.push_back(_digitis[_j] + '0');
				continue;
			}
			_first_half.push_back(_digitis[_j] + '0');
		}

		if (_first_half == _second_half) {
			println("In [{}, {}]: {} is invalid\n", inter.min, inter.max, i);
			invalids += i;
            continue;
		}

#if __PART_2_SOLUTION == 1
		vector<string> _key = {};
		for (int _dd = 0; _dd < _digitis.size() / 2; _dd++) {

			string temp = "";
			for (int _j = 0; _j <= _dd; _j++) {
				temp.push_back(_digitis[(_digitis.size() - 1) - _j] + '0');
			}
			_key.push_back(temp);
		}

		for (string key : _key) {
            string inter_string = _second_half + _first_half;

            if (!is_multiple_of(inter_string.length(), key.length())) {
                continue;
            }

            string _test = "";
            for (int _j = key.length(); _j <= inter_string.length(); _j += key.length()) {
                _test += key;
            }

			if (inter_string == _test) {
				println("In [{}, {}]: {} is invalid because {} == {}\n", inter.min, inter.max, i, key.c_str(), inter_string.c_str());
				invalids += i;
                break;
			}
		}
#endif
	}

	return invalids;
}

int main(void) {
	vector<vector<uint64_t>> lines = read_int_seperator("./test_case.txt", {',', '-'});
	uint64_t sum_of_invalids = 0;

	for (vector<uint64_t> numbers : lines) {
		for (int i = 0; i < numbers.size(); i += 2) {
			sum_of_invalids += cauculuate_invalid_ids_in_interval({(uint_fast64_t)numbers[i], (uint_fast64_t)numbers[i + 1]});
		}
	}

	println("\nSum of invalid ID's: {}\n", sum_of_invalids);
	return 0;
}
