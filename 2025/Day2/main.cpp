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

// NOTE: Esta até deixa o prof. Marco orgolhoso
uint64_t cauculuate_invalid_ids_in_interval(interval inter) {
	uint64_t invalids = 0;

	for (uint64_t i = inter.min; i <= inter.max; i++) {
		vector<uint64_t> _digitis = get_digits(i);

		if (_digitis.size() % 2 != 0) {
			continue;
		}

#if __PART_2_SOLUTION == 0
		string _first_half, _second_half;
		for (int _j = _digitis.size() - 1; _j >= 0; _j--) {
			if (_j >= _digitis.size() / 2) {
				_second_half.push_back(_digitis[_j] + '0');
				continue;
			}
			_first_half.push_back(_digitis[_j] + '0');
		}

		if (_first_half == _second_half) {
			printf("In [%llu, %llu]: %llu is invalid\n", inter.min, inter.max, i);
			invalids += i;
		}
#else

		vector<string> _keys;

		for (int _j = (_digitis.size() / 2) - 1; _j >= 0; _j--) {
            string _temp;
            for (int __k = _digitis.size() - 1; __k >= _j; __k--) {
                _temp.push_back(_digitis[_j] + '0');
                _keys.push_back(_temp);
            }
		}

        for (string _key : _keys) {
            printf("[%s]\t", _key.c_str());
        }
        printf("\n");
#endif
	}

	return invalids;
}

int main(void) {
	vector<vector<uint64_t>> lines = read_int_seperator("./sample.txt", {',', '-'});
	uint64_t sum_of_invalids = 0;

	for (vector<uint64_t> numbers : lines) {
		for (int i = 0; i < numbers.size(); i += 2) {
			sum_of_invalids += cauculuate_invalid_ids_in_interval({(uint_fast64_t)numbers[i], (uint_fast64_t)numbers[i + 1]});
		}
	}

	printf("\nSum of invalid ID's: %llu\n", sum_of_invalids);
	return 0;
}
