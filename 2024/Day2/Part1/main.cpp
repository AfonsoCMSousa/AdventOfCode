#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#define LINE_SIZE 256

// 155 < saves < 269

int main(void)
{
    int save = 0;
    std::ifstream inputFile("example.txt");

    std::string line;
    while (std::getline(inputFile, line))
    {
        bool isSave = false;
        std::istringstream iss(line);
        std::vector<int> numbers;
        int deflects[10] = {0};

        int number;
        while (iss >> number)
        {
            numbers.push_back(number);
        }

        for (int i = 0; i < numbers.size() - 1; i++)
        {
            deflects[i] = numbers[i] - numbers[i + 1];
        }
    }
    printf("%d\n", save);
    inputFile.close();
    return 0;
}