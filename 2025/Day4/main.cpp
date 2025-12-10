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
	bool access;

  public:
	Rool() {
		x = 0;
		y = 0;
		this->exists = false;
		this->access = false;
	}

	Rool(uint32_t x, uint32_t y) {
		this->x = x;
		this->y = y;
		this->exists = true;
		this->access = false;
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

	bool isAccess() {
		return access;
	}

	void setAccess(bool access) {
		this->access = access;
	}
};

class Map {
  private:
	vector<Rool> map;
	uint32_t __size;
	uint32_t height;
	uint32_t width;
	uint32_t accessible_rools;

  public:
	Map(uint32_t rows, uint32_t cols) {
		this->__size = (rows * cols);
		this->height = rows;
		this->width = cols;
		map.resize(this->__size);
	};

	void setRoolPos(uint32_t x, uint32_t y) {
		if (x >= this->width || y >= this->height) {
			throw runtime_error(format("Map is not big enought to enter ({},{}) in it", x, y));
		}
		map[y * this->width + x] = Rool(x, y);
	};

	void setRoolAccess(uint32_t x, uint32_t y) {
		if (x >= this->width || y >= this->height) {
			throw runtime_error(format("Map is not big enought to remove ({},{}) in it", x, y));
		}

		if (!map[y * this->width + x].isExists()) {
			throw runtime_error(format("No Rool found at position ({},{}) to set access", x, y));
		}

		map[y * this->width + x].setAccess(true);
		accessible_rools++;
	};

    void removeRoolPos(uint32_t x, uint32_t y) {
        if (x >= this->width || y >= this->height) {
            throw runtime_error(format("Map is not big enought to remove ({},{}) in it", x, y));
        }
        map[y * this->width + x] = Rool();
    }

	Rool getRoolPos(uint32_t x, uint32_t y) {
		if ((x + (y * this->height)) > __size) {
			throw runtime_error(format("Map is not big enought to get ({},{}) in it", x, y));
		}
		return map[y * this->width + x];
	};

	uint32_t size() {
		return __size;
	};

	uint32_t getAccessibleRoolsCount() {
		return accessible_rools;
	}

	// NOTE: Returns the number of rools nearby, like this:
	// ...
	// .@.
	// @@.
	// would return 2;
	uint32_t getNearbyRools(int32_t x, int32_t y) {
		uint32_t count = 0;

		if (!map[y * this->width + x].isExists()) {
			return 0;
		}

		for (int _y = y - 1; _y <= y + 1; _y++) {
			if (_y < 0 || _y >= this->height) {
				continue;
			}
			for (int _x = x - 1; _x <= x + 1; _x++) {
				if (_x < 0 || _x >= this->width)
					continue;

				if (_x == x && _y == y)
					continue;

				if (this->map[(_y * this->width) + _x].isExists()) {
					count++;
				}
			}
		}

		return count;
	}

	string toString() {
		string result = "";
		for (uint32_t y = 0; y < height; y++) {
			for (uint32_t x = 0; x < width; x++) {
				if (getRoolPos(x, y).isAccess()) {
					result += "x";
				}

				else if (getRoolPos(x, y).isExists()) {
					result += "@";
				}

				else {
					result += ".";
				}
			}
			result += "\n";
		}
		return result;
	}
};

int main(void) {
	vector<vector<char>> map_string = read_char("./test_case.txt");

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

#if __PART_2_SOLUTION == 1
	while (1) {
		uint32_t newly_accessible = 0;
#endif
		for (uint16_t line = 0; line < map_string.size(); line++) {
			for (uint16_t letter = 0; letter < map_string[line].size(); letter++) {
				if (map.getNearbyRools(letter, line) < 4 && map.getRoolPos(letter, line).isExists() && !map.getRoolPos(letter, line).isAccess()) {
					map.setRoolAccess(letter, line);
					if (__PART_2_SOLUTION == 1) 
                        newly_accessible++;
				}
			}
		}

        for (uint16_t line = 0; line < map_string.size(); line++) {
            for (uint16_t letter = 0; letter < map_string[line].size(); letter++) {
                if (map.getRoolPos(letter, line).isAccess()) {
                    map.removeRoolPos(letter, line);
                }
            }
        }

#if __PART_2_SOLUTION == 1
		if (newly_accessible == 0) {
			break;
		}
	}

#endif
	println("Map representation:\n{}", map.toString());
	println("Accessible rools count: {}", map.getAccessibleRoolsCount());

	return 0;
}
