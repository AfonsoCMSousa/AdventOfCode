#include <algorithm>
#include <cctype>
#include <cstdint>
#include <cstdio>
#include <format>
#include <iostream>
#include <print>
#include <stack>
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include <vector>

#define __PART_2_SOLUTION 1

// Default FileIO file:
#include "../include/file_io.cpp"

using namespace std;

typedef struct {
    uint64_t id;
    bool isRotten;
}ingredient_t;

bool contain(vector<uint64_t> vec, uint64_t check) {
    if(vec.empty())
        return false;
    for (uint64_t _c : vec) {
        if(_c == check) {
            return true;
        }
    }
    return false;
}

int main(void) {
	vector<vector<uint64_t>> numbers = read_int_seperator("./sample.txt", {'-'});
    vector<uint64_t> validIDs;
    vector<ingredient_t> ingredients;
    uint64_t rottenCount = 0;
  
    for (uint64_t line = 0; line < numbers.size(); line++) {
        // NOTE: Checking Intervals 
        if (numbers[line].size() == 2) {
            for (uint64_t _interval = numbers[line][0]; _interval <= numbers[line][1] ; _interval++) {
                if(!contain(validIDs, _interval)) {
                    validIDs.push_back(_interval);
                }
            }
            continue;
        }

        // NOTE: Checking ID's
        if (numbers[line].size() == 1) {
            if(!contain(validIDs, numbers[line][0])) {
                ingredients.push_back({numbers[line][0], false});
            } else {
                ingredients.push_back({numbers[line][0], true});
            }
            continue;
        }
    }

    // DEBUG: Print Valid ID' 
    print("Valid ID's: [");
    for (uint64_t _id : validIDs) {
        print("{}, ", _id);
    }
    println("]");

    for (ingredient_t _ing : ingredients) {
        if(_ing.isRotten) {
            rottenCount++;
        }
    }
    println("Rotten Ingredients: {}", rottenCount); 
    println("Fresh Ingredients: {}", ingredients.size() - rottenCount);

    return 0;
}
