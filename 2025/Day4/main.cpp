#include <algorithm>
#include <cctype>
#include <cstdint>
#include <cstdio>
#include <format>
#include <print>
#include <stdexcept>
#include <sys/types.h>
#include <vector>

#define __PART_2_SOLUTION 1

// Default FileIO file:
#include "../include/file_io.cpp"

using namespace std;

class Rool {
  private:
	uint32_t x;
	uint32_t y;
	bool exists;

  public:
	Rool() {
		x = 0;
		y = 0;
		this->exists = false;
	}

	Rool(uint32_t x, uint32_t y) {
		this->x = x;
		this->y = y;
		this->exists = true;
	}

	uint32_t getX() {
		return x;
	};

	uint32_t getY() {
		return y;
	};

	bool isExists() {
		return exists;
	};
};

class Map {
  private:
	vector<Rool> map;
	uint32_t __size;
	uint32_t height;
	uint32_t width;

  public:
	Map(uint32_t rows, uint32_t cols) {
		this->map.resize(rows * cols);
		this->__size = (rows * cols) + 1;
		this->height = rows;
		this->width = cols;
	};

	void setRoolPos(uint32_t x, uint32_t y) {
		if ((x * y) > __size) {
			throw runtime_error(format("Map is not big enought to enter ({},{}) in it", x, y));
		}
		map[x * y] = Rool(x, y);
	};

	Rool getRoolPos(uint32_t x, uint32_t y) {
		if ((x * y) > __size) {
			throw runtime_error(format("Map is not big enought to get ({},{}) in it", x, y));
		}
		return map[x * y];
	};

	uint32_t size() {
		return __size;
	};

	// NOTE: Returns the number of rools nearby, like this:
	// ...
	// .@.
	// @@.
	// would return 2;
	uint32_t getNearbyRools(uint32_t x, uint32_t y) {
		uint32_t count = 0;

		for (int _y = y - 1; _y <= y + 1; _y++) {
			if (_y < 0 || _y >= this->height)
				continue;

			for (int _x = x - 1; _x <= x + 1; _x++) {
				if (_x < 0 || _x >= this->width)
					continue;

				if (_x == x && _y == y)
					continue;

				if (this->map[_y * this->width + _x].isExists()) {
					count++;
				}
			}
		}

		return count;
	}
};

int main(void) {
	vector<vector<char>> map_string = read_char("./sample.txt");

	Map map(map_string.size(), map_string[0].size());

	println("Map size: {} x {}", map_string.size(), map_string[0].size());
	println("Map:");
	for (const auto &line : map_string) {
		for (const auto &letter : line) {
			print("{}", letter);
		}
		println("");
	}

	for (uint16_t line = 0; line < map_string.size(); line++) {
		for (uint16_t letter = 0; letter < map_string[line].size(); letter++) {
			if (map_string[line][letter] == '@') {
				// println("Rool found at position (x:{},y:{})", letter, line);
				map.setRoolPos(letter, line);
			}
		}
	}

	println("Number of Rools arround (x:{}, y:{}) = {}", 2, 0, map.getNearbyRools(2, 0));

	return 0;
}
