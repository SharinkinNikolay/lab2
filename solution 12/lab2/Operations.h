#ifndef Operations
#define Operations

struct Matrix {
    unsigned int height;
    unsigned int width;
    int** insides;
};

struct Matrix createMatrix(char* string);
void printMatrix(struct Matrix);
void printSum(struct Matrix, struct Matrix);
void printSubtraction(struct Matrix, struct Matrix);
struct Matrix multiplication(struct Matrix, struct Matrix);
void freeMatrix(struct Matrix);
void printTranspose(struct Matrix);
int findDet(struct Matrix, int n);

#endif