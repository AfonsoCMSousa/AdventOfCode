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

bool checkVerticaly(std::vector<std::vector<char>> &fileChars, size_t lines, size_t chars)
{
    if (fileChars[lines][chars] == XMAS[0] && (fileChars.size() - lines) > XMAS_SIZE - 1)
    {
        for (size_t i = 0; i < XMAS_SIZE; i++)
        {
            if (fileChars[lines + i][chars] != XMAS[i])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool checkVerticalyReverse(std::vector<std::vector<char>> &fileChars, size_t lines, size_t chars)
{
    if (fileChars[lines][chars] == XMAS[XMAS_SIZE - 1] && fileChars.size() >= XMAS_SIZE && fileChars.size() - lines > XMAS_SIZE - 1)
    {
        for (size_t i = 0; i < XMAS_SIZE; i++)
        {
            if (fileChars[lines + i][chars] != XMAS[(XMAS_SIZE - 1) - i])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool checkHorizontal(std::vector<std::vector<char>> &fileChars, size_t lines, size_t chars)
{
    if (fileChars[lines][chars] == XMAS[0] && (fileChars[lines].size() - chars) >= XMAS_SIZE)
    {
        for (size_t i = 0; i < XMAS_SIZE; i++)
        {
            if (fileChars[lines][chars + i] != XMAS[i])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool checkHorizontalReverse(std::vector<std::vector<char>> &fileChars, size_t lines, size_t chars)
{
    if (fileChars[lines][chars] == XMAS[XMAS_SIZE - 1] && chars <= fileChars[lines].size() - 3)
    {
        for (size_t i = 0; i < XMAS_SIZE; i++)
        {
            if (fileChars[lines][chars + i] != XMAS[(XMAS_SIZE - 1) - i])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool checkDiagonalRight(std::vector<std::vector<char>> &fileChars, size_t lines, size_t chars)
{

    if (fileChars[lines][chars] == XMAS[0] && (fileChars[lines + 3].size() - chars) > XMAS_SIZE - 1 && (fileChars.size() - lines) > XMAS_SIZE - 1)
    {
        for (size_t i = 0; i < XMAS_SIZE; i++)
        {
            if (fileChars[lines + i][chars + i] != XMAS[i])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool checkDiagonalRightReverse(std::vector<std::vector<char>> &fileChars, size_t lines, size_t chars)
{
    if (fileChars[lines][chars] == XMAS[(XMAS_SIZE - 1)] && (fileChars[lines + 3].size() - chars) > XMAS_SIZE - 1 && (fileChars.size() - lines) > XMAS_SIZE - 1)
    {
        for (size_t i = 0; i < XMAS_SIZE; i++)
        {
            if (fileChars[lines + i][chars + i] != XMAS[(XMAS_SIZE - 1) - i])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool checkDiagonalLeft(std::vector<std::vector<char>> &fileChars, size_t lines, size_t chars)
{
    if (fileChars[lines][chars] == XMAS[0] && fileChars.size() >= XMAS_SIZE && fileChars.size() - lines > XMAS_SIZE - 1)
    {
        for (size_t i = 0; i < XMAS_SIZE; i++)
        {
            if (fileChars[lines + i][chars - i] != XMAS[i])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool checkDiagonalLeftReverse(std::vector<std::vector<char>> &fileChars, size_t lines, size_t chars)
{
    if (fileChars[lines][chars] == XMAS[(XMAS_SIZE - 1)] && fileChars.size() >= XMAS_SIZE && fileChars.size() - lines > XMAS_SIZE - 1)
    {
        for (size_t i = 0; i < XMAS_SIZE; i++)
        {
            if (fileChars[lines + i][chars - i] != XMAS[(XMAS_SIZE - 1) - i])
            {
                return false;
            }
        }
        return true;
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
            if (checkVerticaly(fileChars, lines, chars))
            {
                xmasCounter++;
            }

            if (checkVerticalyReverse(fileChars, lines, chars))
            {
                xmasCounter++;
            }

            if (checkHorizontal(fileChars, lines, chars))
            {
                xmasCounter++;
            }

            if (checkHorizontalReverse(fileChars, lines, chars))
            {
                xmasCounter++;
            }

            if (checkDiagonalRight(fileChars, lines, chars))
            {
                xmasCounter++;
            }

            if (checkDiagonalRightReverse(fileChars, lines, chars))
            {
                xmasCounter++;
            }

            if (checkDiagonalLeft(fileChars, lines, chars))
            {
                xmasCounter++;
            }

            if (checkDiagonalLeftReverse(fileChars, lines, chars))
            {
                xmasCounter++;
            }

            printf("%c", fileChars[lines][chars]);
        }
        printf("\n");
    }

    printf("\nXMAS Found:%d\n", xmasCounter);

    return 0;
}