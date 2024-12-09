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

bool isMull(std::vector<std::vector<char>> &text, size_t i, size_t j)
{
    return text[i][j - 2] == 'm' && text[i][j - 1] == 'u' && text[i][j] == 'l';
}

bool isDo(std::vector<std::vector<char>> &text, size_t i, size_t j)
{
    return text[i][j - 1] == 'd' && text[i][j] == 'o';
}

bool isDont(std::vector<std::vector<char>> &text, size_t i, size_t j)
{
    return text[i][j - 4] == 'd' && text[i][j - 3] == 'o' && text[i][j - 2] == 'n' && text[i][j - 1] == '\'' && text[i][j] == 't';
}

int main(void)
{
    int number1 = 0, number2 = 0;

    bool isMullEnable = true;

    u_int64_t total = 0;
    std::vector<std::vector<char>> text = readCharFile("input.txt");

    for (u_int64_t i = 0; i < text.size(); i++)
    {
        for (u_int64_t j = 0; j < text[i].size(); j++)
        {

            if (isDo(text, i, j))
            {
                isMullEnable = true;
            }

            if (isDont(text, i, j))
            {
                isMullEnable = false;
            }

            if (isMull(text, i, j) && isMullEnable)
            {
                if (text[i][j + 1] == '(')
                {
                    int ofset = 0;
                    std::vector<char> temp;

                    while (text[i][j + 2 + ofset] != ',')
                    {
                        temp.push_back(text[i][j + 2 + ofset]);
                        ofset++;
                    }

                    std::string tempStr1(temp.begin(), temp.end());
                    number1 = atoi(tempStr1.c_str());

                    bool isValidMull = true;

                    for (size_t jj = 0; jj < tempStr1.size(); jj++)
                    {
                        if (!(tempStr1[jj] >= '0' && tempStr1[jj] <= '9'))
                        {
                            isValidMull = false;
                            break;
                        }
                    }

                    temp.clear();
                    ofset++;

                    while (text[i][j + 2 + ofset] != ')')
                    {
                        temp.push_back(text[i][j + 2 + ofset]);
                        ofset++;
                    }

                    std::string tempStr2(temp.begin(), temp.end());
                    number2 = atoi(tempStr2.c_str());

                    for (size_t jj = 0; jj < tempStr2.size(); jj++)
                    {
                        if (!(tempStr2[jj] >= '0' && tempStr2[jj] <= '9'))
                        {
                            isValidMull = false;
                            break;
                        }
                    }

                    if (isValidMull)
                    {
                        total += number1 * number2;

                        printf("[%3d,%3d] = %d\n", number1, number2, number1 * number2);
                    }
                }
            }
        }
    }
    printf("%llu\n", total);
    return 0;
}