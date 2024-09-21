#include <stdio.h>
#include <stdlib.h>

#define MATRIX_SIZE 2
#define MOD 26
void multiplyMatrices(int a[MATRIX_SIZE][MATRIX_SIZE], int b[MATRIX_SIZE][MATRIX_SIZE], int result[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            result[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                result[i][j] += (a[i][k] * b[k][j]) % MOD;
            }
            result[i][j] %= MOD;
        }
    }
}
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; 
}
int determinant(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % MOD;
}
int inverseMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE], int inverse[MATRIX_SIZE][MATRIX_SIZE]) {
    int det = determinant(matrix);
    int invDet = modInverse(det, MOD);
    
    if (invDet == -1) {
        return -1;  
    }
    
    inverse[0][0] = (matrix[1][1] * invDet) % MOD;
    inverse[0][1] = (-matrix[0][1] * invDet) % MOD;
    inverse[1][0] = (-matrix[1][0] * invDet) % MOD;
    inverse[1][1] = (matrix[0][0] * invDet) % MOD;

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            inverse[i][j] = (inverse[i][j] + MOD) % MOD;  
        }
    }
    return 0;  
}
void recoverKey(int plaintext[MATRIX_SIZE][MATRIX_SIZE], int ciphertext[MATRIX_SIZE][MATRIX_SIZE], int key[MATRIX_SIZE][MATRIX_SIZE]) {
    int invPlaintext[MATRIX_SIZE][MATRIX_SIZE];
    if (inverseMatrix(plaintext, invPlaintext) == -1) {
        printf("No inverse matrix found for the plaintext.\n");
        return;
    }
    
    multiplyMatrices(invPlaintext, ciphertext, key);
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            key[i][j] = (key[i][j] + MOD) % MOD;  
        }
    }
}
void printMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int plaintext[MATRIX_SIZE][MATRIX_SIZE];
    int ciphertext[MATRIX_SIZE][MATRIX_SIZE];
    int key[MATRIX_SIZE][MATRIX_SIZE];
    printf("Enter the 2x2 plaintext matrix (row by row):\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            scanf("%d", &plaintext[i][j]);
        }
    }

    printf("Enter the 2x2 ciphertext matrix (row by row):\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            scanf("%d", &ciphertext[i][j]);
        }
    }
    recoverKey(plaintext, ciphertext, key);
    printf("\nRecovered key matrix:\n");
    printMatrix(key);

    return 0;
}

