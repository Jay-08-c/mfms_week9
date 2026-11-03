#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "utilities.h"

/* Reads a line, removes the newline, and rejects input that is too long. */
static int readLine(const char *prompt, char *buffer, int size)
{
    size_t length;
    int ch;

    printf("%s", prompt);

    if (fgets(buffer, size, stdin) == NULL) {
        return 0; /* End of input */
    }

    length = strlen(buffer);

    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
    } else if (!feof(stdin)) {
        while ((ch = getchar()) != '\n' && ch != EOF) {
            /* Discard the rest of an overlong input line. */
        }
        printf("Input is too long. Please try again.\n");
        return -1;
    }

    return 1;
}

/* Reads non-empty text and stores it in answer. */
int readText(const char *prompt, char *answer, int size)
{
    char line[256];
    char *start;
    size_t length;
    int result;

    if (size <= 0) {
        return 0;
    }

    while (1) {
        result = readLine(prompt, line, sizeof(line));

        if (result == 0) {
            return 0;
        }
        if (result < 0) {
            continue;
        }

        start = line;

        while (isspace((unsigned char)*start)) {
            start++;
        }

        length = strlen(start);

        while (length > 0 && isspace((unsigned char)start[length - 1])) {
            start[--length] = '\0';
        }

        if (length == 0) {
            printf("This field cannot be left empty.\n");
        } else if (length >= (size_t)size) {
            printf("Please enter fewer characters (maximum %d).\n", size - 1);
        } else {
            strcpy(answer, start);
            return 1;
        }
    }
}

/* Reads and validates an integer. Returns 1 on success, 0 on end of input. */
int readInt(const char *prompt, int *value)
{
    char line[128];
    char *end;
    long number;
    int result;

    while (1) {
        result = readLine(prompt, line, sizeof(line));

        if (result == 0) {
            return 0;
        }
        if (result < 0) {
            continue;
        }

        errno = 0;
        number = strtol(line, &end, 10);

        while (isspace((unsigned char)*end)) {
            end++;
        }

        if (line[0] == '\0' || end == line || *end != '\0' ||
            errno == ERANGE || number < -2147483647L - 1 ||
            number > 2147483647L) {
            printf("Please enter a valid whole number.\n");
        } else {
            *value = (int)number;
            return 1;
        }
    }
}

/* Reads and validates a number, including decimal values. */
int readDouble(const char *prompt, double *value)
{
    char line[128];
    char *end;
    double number;
    int result;

    while (1) {
        result = readLine(prompt, line, sizeof(line));

        if (result == 0) {
            return 0;
        }
        if (result < 0) {
            continue;
        }

        errno = 0;
        number = strtod(line, &end);

        while (isspace((unsigned char)*end)) {
            end++;
        }

        if (line[0] == '\0' || end == line || *end != '\0' ||
            errno == ERANGE) {
            printf("Please enter a valid number.\n");
        } else if (number < 0) {
            printf("The value cannot be negative.\n");
        } else {
            *value = number;
            return 1;
        }
    }
}
