#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>

#define LINE_SIZE 256

std::vector<std::vector<char>> readCharFile(const char *filePath);

std::vector<std::vector<int>> readIntFile(const char *filePath);

std::vector<std::vector<int>> derivatives(std::vector<std::vector<int>> numbers); // Declare function

bool isSameSignal(std::vector<int> derivative);

// 155 < saves < 269

int main(void)
{
    int save = 0;
    int saved = 0;

    bool isSave = true;

    std::vector<std::vector<int>> numbers = readIntFile("input.txt");
    std::vector<std::vector<int>> derivative = derivatives(numbers);

    for (size_t i = 0; i < derivative.size(); i++)
    {
        isSave = true;
        for (size_t j = 0; j < numbers[i].size(); j++)
        {
            printf("%3d", numbers[i][j]);
        }
        printf("\n");
        for (size_t j = 0; j < derivative[i].size(); j++)
        {
            printf("%3d", derivative[i][j]);
        }
        printf("\n");

        if (isSameSignal(derivative[i]))
        {
            for (size_t j = 0; j < derivative[i].size(); j++)
            {
                if (derivative[i][j] < 0)
                {
                    derivative[i][j] *= -1;
                }

                if (derivative[i][j] > 3 || derivative[i][j] < 1)
                {
                    printf("is not save because %d > 3 or %d < 1\n\n", derivative[i][j], derivative[i][j]);
                    isSave = false;
                    break;
                }
            }
        }
        else
        {
            printf("is not save because its not the same signal\n\n");
            isSave = false;
        }

        if (isSave)
        {
            printf("\n");
            save++;
        }
        else
        {
            for (size_t k = 0; k < numbers[i].size(); k++)
            {
                std::vector<int> temp = numbers[i];
                temp.erase(temp.begin() + k);
                std::vector<int> tempDerivative = derivatives({temp})[0];

                if (isSameSignal(tempDerivative))
                {
                    bool tempIsSave = true;
                    for (size_t j = 0; j < tempDerivative.size(); j++)
                    {
                        if (tempDerivative[j] < 0)
                        {
                            tempDerivative[j] *= -1;
                        }

                        if (tempDerivative[j] > 3 || tempDerivative[j] < 1)
                        {
                            tempIsSave = false;
                            break;
                        }
                    }

                    if (tempIsSave)
                    {
                        save++;
                        break;
                    }
                }
            }
        }
    }

    printf("Save: %d\nSaved: %d\n", save, save + saved);

    return 0;
}

std::vector<std::vector<int>> derivatives(std::vector<std::vector<int>> numbers)
{
    std::vector<std::vector<int>> derivative(numbers.size());

    for (size_t i = 0; i < numbers.size(); i++)
    {
        for (size_t j = 0; j < numbers[i].size() - 1; j++)
        {
            derivative[i].push_back(numbers[i][j] - numbers[i][j + 1]);
        }
    }

    return derivative;
}

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

bool isSameSignal(std::vector<int> derivative)
{
    for (u_int16_t j = 0; j < derivative.size(); j++)
    {
        if (derivative[0] > 0)
        {
            if (derivative[j] <= 0)
            {
                return false;
            }
        }
        else if (derivative[0] < 0)
        {
            if (derivative[j] >= 0)
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    return true;
}