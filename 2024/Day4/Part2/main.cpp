#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>

#define XMAS_SIZE 4
char XMAS[XMAS_SIZE + 1] = {'X', 'M', 'A', 'S', '\0'};

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

bool checkXMAS(std::vector<std::vector<char>> &fileChars, size_t lines, size_t chars)
{
    if (fileChars[lines][chars] == XMAS[2] && lines >= 1 && chars >= 1 && fileChars.size() - lines > 1 && fileChars[lines].size() - chars > 1)
    {
        if (fileChars[lines - 1][chars - 1] == XMAS[1])
        {
            // M.
            // .A
            // M.
            if (fileChars[lines + 1][chars - 1] == XMAS[1])
            {
                // M.S
                // .A
                // M.S
                if (fileChars[lines - 1][chars + 1] == XMAS[3] && fileChars[lines + 1][chars + 1] == XMAS[3])
                {
                    return true;
                }
                return false;
            }
            else if (fileChars[lines + 1][chars - 1] == XMAS[3])
            {
                // M.M
                // .A
                // S.S
                if (fileChars[lines - 1][chars + 1] == XMAS[1] && fileChars[lines + 1][chars + 1] == XMAS[3])
                {
                    return true;
                }
                return false;
            }
            // M.
            // .A
            // S.
        }
        else if (fileChars[lines - 1][chars - 1] == XMAS[3]) // S
        {
            // S.
            // .A
            // S.
            if (fileChars[lines + 1][chars - 1] == XMAS[3])
            {
                // S.M
                // .A
                // S.M
                if (fileChars[lines - 1][chars + 1] == XMAS[1] && fileChars[lines + 1][chars + 1] == XMAS[1])
                {
                    return true;
                }
                return false;
            }
            else if (fileChars[lines + 1][chars - 1] == XMAS[1])
            {
                // S.S
                // .A
                // M.M
                if (fileChars[lines - 1][chars + 1] == XMAS[3] && fileChars[lines + 1][chars + 1] == XMAS[1])
                {
                    return true;
                }
                return false;
            }
            // S.
            // .A
            // M.
        }
    }
    return false;
}

int main(void)
{
    std::vector<std::vector<char>> fileChars = readCharFile("input.txt");

    int xmasCounter = 0;

    for (size_t lines = 0; lines < fileChars.size(); lines++)
    {
        for (size_t chars = 0; chars < fileChars[lines].size(); chars++)
        {
            if (checkXMAS(fileChars, lines, chars))
            {
                xmasCounter++;
            }

            printf("%c", fileChars[lines][chars]);
        }
        printf("\n");
    }

    printf("\nX-MAS Found:%d\n", xmasCounter);

    return 0;
}