#include "Operations.h"
#include "Reading.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Matrix createMatrix(char* string) {
    struct Matrix m;
    m.height = findHeight(string);
    m.width = findWidth(string);
    int** arr = (int**)calloc(m.width, sizeof(int));
    for (int i = 0; i < m.width; i++) {
        arr[i] = (int*)calloc(m.height, sizeof(int));
    }

    int j = 0;
    int i = 0;

    for (int index = 0; index < strlen(string); index++) {
        if (string[index] == '/') {
            i++;
            j = 0;
        }
        else if (isdigit(string[index])) {
            arr[i][j] *= 10;
            char c[1] = { string[index] };
            arr[i][j] += atoi(c);
        }
        else if (string[index] == ' ') {
            j++;
        }
    }
    m.insides = arr;
    return m;
}

void printMatrix(struct Matrix a) {
    for (int i = 0; i < a.height; i++) {
        for (int j = 0; j < a.width; j++) {
            printf("%d ", a.insides[i][j]);
        }
        printf("\n");
    }
}

void printSum(struct Matrix a, struct Matrix b) {
    if (!(a.height == b.height && a.width == b.width)) {
        printf("ERROR: matrixes have different sizes\n");
        return;
    }
    for (int i = 0; i < a.height; i++) {
        for (int j = 0; j < a.width; j++) {
            printf("%d ", a.insides[i][j] + b.insides[i][j]);
        }
        printf("\n");
    }
}

void printSubtraction(struct Matrix a, struct Matrix b) {
    if (!(a.height == b.height && a.width == b.width)) {
        printf("ERROR: matrixes have different sizes\n");
        return;
    }
    for (int i = 0; i < a.height; i++) {
        for (int j = 0; j < a.width; j++) {
            printf("%d ", a.insides[i][j] - b.insides[i][j]);
        }
        printf("\n");
    }
}

void printTranspose(struct Matrix a) {
    for (int i = 0; i < a.width; i++) {
        for (int j = 0; j < a.height; j++) {
            printf("%d ", a.insides[j][i]);
        }
        printf("\n");
    }
}

void freeMatrix(struct Matrix a) {
    for (int i = 0; i < a.width; i++) {
        free(a.insides[i]);
    }
}


struct Matrix createEmptyMatrix(int height, int width) {
    struct Matrix m;
    m.height = height;
    m.width = width;
    int** arr = (int**)calloc(m.width, sizeof(int));
    for (int i = 0; i < m.width; i++) {
        arr[i] = (int*)calloc(m.height, sizeof(int));
    }
    m.insides = arr;
    return m;
}

struct Matrix multiplication(struct Matrix a, struct Matrix b) {
    if (a.width != b.height) {
        printf("ERROR: Matrixes are not compatable to multiply\n");
        exit(1);
    }
    struct Matrix res = createEmptyMatrix(a.height, b.width);
    for (int i = 0; i < a.height; i++) {
        for (int j = 0; j < b.width; j++) {
            int sum = 0;
            for (int k = 0; k < a.width; k++) {
                sum += a.insides[i][k] * b.insides[k][j];
            }
            res.insides[i][j] = sum;
        }
    }
    return res;
}

struct Matrix Gauss(struct Matrix a) {
    for (int i = 0; i < a.height; i++) {
        for (int j = i + 1; j < a.height; j++) {
            float ratio = ((float)a.insides[j][i] / (float)a.insides[i][i]);
            for (int k = 0; k < a.height; k++) {
                printf("from %d to ", a.insides[j][k]);
                a.insides[j][k] = a.insides[j][k] - ratio * a.insides[i][k];
                printf("%d\n", a.insides[j][k]);
            }
        }
    }

    printMatrix(a);
    return a;
}

struct Matrix turnMatrixIntoMinor(struct Matrix a, int amount, int i, int j) {
    int di = 0;
    struct Matrix temp_matrix = createEmptyMatrix(a.height, a.width);
    for (int ki = 0; ki < amount - 1; ki++)
    {
        if (i == i) di = 1;
        int dj = 0;
        for (int kj = 0; kj < amount - 1; kj++)
        {
            if (kj == j) dj = 1;
            temp_matrix.insides[ki][kj] = a.insides[ki + di][kj + dj];
        }
    }
    return temp_matrix;
}

int findDet(struct Matrix a, int n) { // n = height
    int det = 0;
    int siqn = 1;
    struct Matrix temp_m = createEmptyMatrix(n, n);
    if (n < 1) {
        printf("ERROR: wrong matrix size\n");
        exit(1);
    }
    else if (n == 1) {
        return a.insides[0][0];
    }
    else if (n == 2) {
        return a.insides[0][0] * a.insides[1][1] - a.insides[1][0] * a.insides[0][1];
    }
    else {
        for (int i = 0; i < n; i++) {
            det = det + siqn * a.insides[i][0] * findDet((turnMatrixIntoMinor(a, n, i, 0)), n - 1);
            siqn *= -1;
        }
    }
    return det;
}