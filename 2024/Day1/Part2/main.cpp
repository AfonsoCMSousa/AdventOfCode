#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <algorithm> // Include algorithm header for std::sort

#define LINE_SIZE 14
#define INT_SIZE 2046
#define LINES 1000

int main(void)
{
    char *buffer = (char *)malloc(sizeof(char) * LINE_SIZE);

    int *Array1 = (int *)malloc(sizeof(int) * INT_SIZE);
    int Array1_INDEX = 0;
    int *Array2 = (int *)malloc(sizeof(int) * INT_SIZE);
    int Array2_INDEX = 0;

    std::ifstream inputFile("input.txt");
    if (!inputFile)
    {
        fprintf(stderr, "Unable to open file");
        exit(1);
    }

    while (inputFile.getline(buffer, LINE_SIZE))
    {
        for (size_t i = 0; i < LINE_SIZE; i++)
        {
            if (buffer[i] == ' ')
            {
                Array1[Array1_INDEX] = atoi(buffer);
                Array1_INDEX++;

                char __temp[14];
                int __tempINDEX = 0;
                for (size_t j = i; j < LINE_SIZE - 1; j++)
                {
                    __temp[__tempINDEX] = buffer[j];
                    __tempINDEX++;
                }
                Array2[Array2_INDEX] = atoi(__temp);
                Array2_INDEX++;
                break;
            }
        }
    }
    inputFile.close(); // Close the file

    std::sort(Array1, Array1 + Array1_INDEX); // Sort Array1
    std::sort(Array2, Array2 + Array2_INDEX); // Sort Array2

    u_int64_t total = 0;

    for (size_t i = 0; i < Array1_INDEX; i++)
    {
        int count = 0;
        for (size_t j = 0; j < Array2_INDEX; j++)
        {
            if (Array1[i] == Array2[j])
            {
                count++;
            }
        }

        if (count)
        {
            total += Array1[i] * count;
        }
    }

    printf("%llu\n", total);

    free(Array2);
    free(Array1);
    free(buffer);
    return 0;
}