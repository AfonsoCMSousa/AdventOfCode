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
            lines[*lineCount][numCount] = atoi(token);
            numCount++;
            token = strtok(NULL, " ");
        }
        (*lineCount)++;
    }

    fclose(file);
    return lines;
}

typedef enum orientation
{
    UP, // 0
    RIGHT,
    DOWN,
    LEFT
} orientation;

typedef struct guard
{
    int x;
    int y;

    orientation rotation;
} guard;

// Yeah... C now.. Advent was too easy

int main(void)
{
    int FileSIZE = 0;
    int charsPerLine = 0;

    u_int32_t movementCount = 1;
    bool isOutOFBounds = false;
    char **textFile = readCharFile("input.txt", &FileSIZE);

    guard myGuard = {0};

    // Find the guard
    for (size_t lines = 0; lines < FileSIZE; lines++)
    {
        charsPerLine = 0;
        while (!(textFile[lines][charsPerLine] == ' ' || (textFile[lines][charsPerLine]) == '\n'))
        {
            charsPerLine++;
        }
        // printf("[%d] = %s", charsPerLine, textFile[lines]); // Check Array of Strings (*string)

        for (size_t chars = 0; chars < charsPerLine; chars++)
        {
            // find the guard
            switch (textFile[lines][chars])
            {
            case '^':
                myGuard.x = lines;
                myGuard.y = chars;
                myGuard.rotation = UP;
                break;

            case 'v':
                myGuard.x = lines;
                myGuard.y = chars;
                myGuard.rotation = DOWN;
                break;

            case '>':
                myGuard.x = lines;
                myGuard.y = chars;
                myGuard.rotation = RIGHT;
                break;

            case '<':
                myGuard.x = lines;
                myGuard.y = chars;
                myGuard.rotation = LEFT;
                break;

            default:
            }
        }
    }

    while (!isOutOFBounds)
    {
        printf("[%2d][%2d] with [%d] = '%c' looking at", myGuard.x, myGuard.y, myGuard.rotation, textFile[myGuard.x][myGuard.y]);

        switch (myGuard.rotation)
        {
        case UP:
            if ((myGuard.x - 1) < 0)
            {
                isOutOFBounds = true;
                break;
            }

            printf(" [%d][%d]\'%c\'\n", myGuard.x - 1, myGuard.y, textFile[myGuard.x - 1][myGuard.y]);

            if (textFile[myGuard.x - 1][myGuard.y] == '#')
            {
                myGuard.rotation = RIGHT;
            }
            else
            {
                if (!(textFile[myGuard.x][myGuard.y] == 'X'))
                {
                    textFile[myGuard.x][myGuard.y] = 'X';
                    movementCount++;
                }
                myGuard.x--;
            }
            break;
        case RIGHT:
            if ((myGuard.y + 1) > charsPerLine)
            {
                isOutOFBounds = true;
                break;
            }

            printf(" [%d][%d]\'%c\'\n", myGuard.x, myGuard.y + 1, textFile[myGuard.x][myGuard.y + 1]);

            if (textFile[myGuard.x][myGuard.y + 1] == '#')
            {
                myGuard.rotation = DOWN;
            }
            else
            {
                if (!(textFile[myGuard.x][myGuard.y] == 'X'))
                {
                    textFile[myGuard.x][myGuard.y] = 'X';
                    movementCount++;
                }
                myGuard.y++;
            }

            break;
        case DOWN:
            if ((myGuard.x + 1) > FileSIZE - 1)
            {
                isOutOFBounds = true;
                break;
            }

            printf(" [%d][%d] \'%c\'\n", myGuard.x + 1, myGuard.y, textFile[myGuard.x + 1][myGuard.y]);

            if (textFile[myGuard.x + 1][myGuard.y] == '#')
            {
                myGuard.rotation = LEFT;
            }
            else
            {
                if (!(textFile[myGuard.x][myGuard.y] == 'X'))
                {
                    textFile[myGuard.x][myGuard.y] = 'X';
                    movementCount++;
                }
                myGuard.x++;
            }

            break;
        case LEFT:
            if ((myGuard.y - 1) < 0)
            {
                isOutOFBounds = true;
                break;
            }

            printf(" [%d][%d]\'%c\'\n", myGuard.x, myGuard.y - 1, textFile[myGuard.x][myGuard.y - 1]);

            if (textFile[myGuard.x][myGuard.y - 1] == '#')
            {
                myGuard.rotation = UP;
            }
            else
            {
                if (!(textFile[myGuard.x][myGuard.y] == 'X'))
                {
                    textFile[myGuard.x][myGuard.y] = 'X';
                    movementCount++;
                }
                myGuard.y--;
            }

            break;
        default:
            fprintf(stderr, "Something worng happend?");
            return 1;
            break;
        }
    }

    printf("\nThe guard is at: [%d][%d] with [%d] orientation = \'%c\'\n", myGuard.x, myGuard.y, myGuard.rotation, textFile[myGuard.x][myGuard.y]);
    printf("Movent made by the gard: %u\n", movementCount);
    return 0;
}