#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>

std::vector<std::vector<char>> readCharFile(const char *filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        return std::vector<std::vector<char>>();
    }

    std::vector<std::vector<char>> lines;
    std::string line;

    while (std::getline(file, line))
    {
        std::vector<char> charLine(line.begin(), line.end());
        lines.push_back(charLine);
    }

    file.close();
    return lines;
}

std::vector<std::vector<int>> readIntFile(const char *filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        return std::vector<std::vector<int>>();
    }

    std::vector<std::vector<int>> lines;
    std::string line;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::vector<int> intLine;
        int number;
        while (iss >> number)
        {
            intLine.push_back(number);
        }
        lines.push_back(intLine);
    }

    file.close();
    return lines;
}

int main(void)
{
    std::vector<std::vector<char>> text = readCharFile("example.txt");

    for (size_t i = 0; i < text.size(); i++)
    {
        for (size_t j = 0; j < text[i].size(); j++)
        {
            printf("%c", text[i][j]);
        }
        printf("\n");
    }

    return 0;
}