#include "Reading.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


char* readMatrixFromFile(char* fileName) {
    FILE* file = fopen(fileName, "r");
    fseek(file, 0, SEEK_END);
    int sz = ftell(file);
    if (sz == 1) {
        printf("TXT file is empty\n");
        exit(1);
    }
    fseek(file, 0, 0);
    char* string = (char*)calloc(sz, sizeof(char));
    fgets(string, sz, file);
    fclose(file);
    return string;
}

int findHeightReading(char* string) {
    int count = 1;
    for (int i = 0; i < strlen(string); i++) {
        if (string[i] == '/') {
            count++;
        }
    }
    return count;
}

int findWidth(char* string) {
    int count = 1;
    for (int i = 0; i < strlen(string); i++) {
        if (string[i] == ' ') {
            count++;
        }
        if (string[i] == '/') {
            break;
        }
    }
    return count;
}