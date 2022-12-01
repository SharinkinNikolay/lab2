#include <stdio.h>
#include <stdlib.h>

#include "Reading.c"
#include "Operations.c"

int workingWithUser(struct Matrix m1, struct Matrix m2) {

    char command = ' ';
    struct Matrix mult = multiplication(m1, m2);
    scanf("%c", &command);
    switch (command) {
    case '1':
        printSum(m1, m2);
        break;
    case '2':
        printSubtraction(m1, m2);
        break;
    case '3':
        printTranspose(m1);
        break;
    case '4':
        printTranspose(m2);
        break;
    case '5':
        printMatrix(mult);
        break;
    case '6':
        if (m1.height != m1.width) {
            printf("ERROR: This matrix is not square matrix\n");
            break;
        }
        printf("%d\n", findDet(m1, m1.height));
        break;
    case '7':
        if (m2.height != m2.width) {
            printf("ERROR: This matrix is not square matrix\n");
            break;
        }
        printf("%d\n", findDet(m2, m2.height));
        break;
    case '8':
        freeMatrix(m1);
        freeMatrix(m2);
        freeMatrix(mult);
        printf("Good bye\n");
        return 0;
    default:
        break;
    }
    return 1;
}

int main(void) {
    struct Matrix m1 = createMatrix(readMatrixFromFile("matrix1.txt"));
    struct Matrix m2 = createMatrix(readMatrixFromFile("matrix2.txt"));

    printf("Welcome to the matrix calculator\n");
    printf("1: sum\n2: subtraction\n3: transpose fisrt matrix\n");
    printf("4: transpose second matrix\n5: multiplacion\n6: find determinant of first matrix\n");
    printf("7: find determinant of second matrix\n8: exit the program\n");
    while (workingWithUser(m1, m2));

    return 0;
}