#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>

// I Dont know how this works, I just tryied swaping stuff arround

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
        std::string number;
        while (std::getline(iss, number, '|'))
        {
            std::istringstream subiss(number);
            std::string subnumber;
            while (std::getline(subiss, subnumber, ','))
            {
                intLine.push_back(std::stoi(subnumber));
            }
        }
        lines.push_back(intLine);
    }

    file.close();
    return lines;
}

typedef struct Rule
{
    int size = 0;
    int *rules = nullptr; // Initialize rules to nullptr
} Rule;

bool contains(Rule rules, int check)
{
    for (size_t i = 0; i < rules.size; i++)
    {
        if (rules.rules[i] == check)
        {
            return true;
        }
    }
    return false;
}

void verify(std::__1::vector<std::__1::vector<int>> &intFile, size_t lines, size_t ints, Rule Rules[100], bool &isValidRule, int &retFlag)
{
    retFlag = 1;
    int key = intFile[lines][ints];
    /*
    printf("Key :%d\n", key);
    for (size_t j = 0; j < Rules[key].size; j++)
    {
        printf("[%d]", Rules[key].rules[j]);
    }
    printf("\n");
    */

    if ((!contains(Rules[key], intFile[lines][ints + 1])) && ints < intFile[lines].size() - 1)
    {
        // printf("failed!\n");
        isValidRule = false;
        {
            retFlag = 2;
            return;
        };
    }
}

int main(void)
{
    std::vector<std::vector<int>> intFile = readIntFile("input.txt");

    Rule Rules[100] = {0};

    u_int64_t total = 0;
    u_int64_t totalSaved = 0;

    bool isRules = true;
    printf("\nDysplaying Rules:\n\n");

    for (size_t lines = 0; lines < intFile.size(); lines++)
    {
        if (intFile[lines].size() == 0 && isRules)
        {
            printf("\nDysplaying Commands\n");
            isRules = false;
            continue;
        }

        bool isValidRule = true;

        for (size_t ints = 0; ints < intFile[lines].size(); ints++)
        {
            if (isRules)
            {
                int ruleIndex = intFile[lines][0];
                if (ruleIndex >= 100)
                    continue;

                int *temp = Rules[ruleIndex].rules;

                temp = (int *)realloc(temp, (Rules[ruleIndex].size + 1) * sizeof(int));
                if (temp == nullptr)
                {
                    std::cerr << "Memory allocation failed" << std::endl;
                    exit(1);
                }
                temp[Rules[ruleIndex].size] = intFile[lines][1];

                Rules[ruleIndex].rules = temp;
                Rules[ruleIndex].size += 1;
                ints++;
            }
            else
            {
                int retFlag;
                verify(intFile, lines, ints, Rules, isValidRule, retFlag);

                if (retFlag == 2)
                    break;
            }
        }

        if (!isRules)
        {
            for (size_t ints = 0; ints < intFile[lines].size(); ints++)
            {
                printf("%2u,", intFile[lines][ints]);
            }

            if (isValidRule)
            {
                printf("\nValid!\n\n");
                total += intFile[lines][intFile[lines].size() / 2];
            }
            else
            {
                isValidRule = true;
                for (size_t i = 0; i < intFile[lines].size(); i++)
                {
                    for (size_t j = 0; j < intFile[lines].size(); j++)
                    {
                        if (contains(Rules[intFile[lines][i]], intFile[lines][j]))
                        {
                            int aux = intFile[lines][i];
                            intFile[lines][i] = intFile[lines][j];
                            intFile[lines][j] = aux;
                        }
                    }
                }

                printf("\n");
                for (size_t ints = 0; ints < intFile[lines].size(); ints++)
                {
                    printf("%2u,", intFile[lines][ints]);
                }
                printf("\n");

                if (isValidRule)
                {
                    printf("Can be saved!\n");
                    totalSaved += intFile[lines][intFile[lines].size() / 2];
                }
                else
                {
                    printf("Can't be saved!\n");
                }
            }
        }
    }

    printf("Rules: \n");

    for (size_t i = 0; i < 100; i++)
    {
        if (Rules[i].size == 0)
        {
            continue;
        }

        printf("[%zu] -> ", i);
        for (size_t j = 0; j < Rules[i].size; j++)
        {
            printf("[%d]", Rules[i].rules[j]);
        }
        printf("\n");
    }

    printf("Total: %llu\nTotal Saved: %llu\n", total, totalSaved);

    // Free any possible pointer
    for (size_t i = 0; i < 100; i++)
    {
        free(Rules[i].rules);
    }

    return 0;
}