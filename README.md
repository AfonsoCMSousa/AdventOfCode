# AdventOfCode GitRep
This repository contains my solutions for the Advent of Code challenges. Each year, I participate in the event and solve the puzzles using various programming languages and techniques.

## Repository Structure
- `yearXXXX/`: Contains solutions for the year XXXX. Each folder is named after the year of the Advent of Code event.

## Important
In every folder that doesnt have a Part1 and Part2 folder, change the line that says:
```cpp
#define __PART_2_SOLUTION 1 // 1 = Part 2 --- 0 = Part 1
```

### How to run:
Inside each ```yyyy/DayX/``` directory, you can compile and run the provided C++ code using the following command:
```bash
g++ -std=c++23 -O2 ./main.cpp -o ./run
```

### For C solutions: 
```bash
gcc -O2 ./main.c -o ./run
```
