#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

char **readCharFile(const char *filePath, int *lineCount)
{
    FILE *file = fopen(filePath, "r");
    if (!file)
    {
        *lineCount = 0;
        return NULL;
    }

    char **lines = NULL;
    char line[1024];
    *lineCount = 0;

    while (fgets(line, sizeof(line), file))
    {
        lines = realloc(lines, sizeof(char *) * (*lineCount + 1));
        lines[*lineCount] = strdup(line);
        (*lineCount)++;
    }

    fclose(file);
    return lines;
}

int **readIntFile(const char *filePath, int *lineCount)
{
    FILE *file = fopen(filePath, "r");
    if (!file)
    {
        *lineCount = 0;
        return NULL;
    }

    int **lines = NULL;
    char line[1024];
    *lineCount = 0;

    while (fgets(line, sizeof(line), file))
    {
        lines = realloc(lines, sizeof(int *) * (*lineCount + 1));
        lines[*lineCount] = NULL;
        int number, numCount = 0;
        char *token = strtok(line, " ");
        while (token)
        {
            lines[*lineCount] = realloc(lines[*lineCount], sizeof(int) * (numCount + 1));
            lines[*lineCount][numCount] = strtol(token, NULL, 10);
            numCount++;
            token = strtok(NULL, " ");
        }
        (*lineCount)++;
    }

    fclose(file);
    return lines;
}

bool evaluate(int numbers[], int n, int target, int current, int index)
{
    if (index == n)
    {
        return current == target;
    }

    // Try addition
    if (evaluate(numbers, n, target, current + numbers[index], index + 1))
    {
        return true;
    }

    // Try multiplication
    if (evaluate(numbers, n, target, current * numbers[index], index + 1))
    {
        return true;
    }

    return false;
}

bool isTargetAchievable(int numbers[], int n)
{
    if (n <= 1)
        return false;
    int target = numbers[0];
    return evaluate(numbers, n, target, numbers[1], 2);
}

int main(void)
{
    int lineSize;
    u_int64_t sumOfAchievableTargets = 0;
    int **intFile = readIntFile("input.txt", &lineSize);

    for (size_t line = 0; line < lineSize; line++)
    {
        size_t counter = 0;
        while (!(intFile[line][counter] == '\0'))
        {
            // printf("%8d,", intFile[line][counter]);
            counter++;
        }
        // printf("\n");

        if (isTargetAchievable(intFile[line], counter))
        {
            printf("Target is achievable for line %zu\n", line);
            sumOfAchievableTargets += intFile[line][0];
        }
        else
        {
            printf("Target is not achievable for line %zu\n", line);
        }
    }

    // first idea to solve the problem
    /* for (size_t line = 0; line < lineSize; line++)
    {
        bool *isMulOrSum = calloc(false, sizeof(bool) * (LenByLine[line] - 2));
        int resultExpected = intFile[line][0];
        int resultCalculated = 0;
        for (size_t i = 1; i < LenByLine[line] - 1; i++)
        {
            resultCalculated += operation(false, intFile[line][i], intFile[line][i + 1]);
        }
    } */

    printf("\nSum of achivables: %llu\n", sumOfAchievableTargets);

    for (size_t line = 0; line < lineSize; line++)
    {
        free(intFile[line]);
    }
    free(intFile);
    return 0;
}