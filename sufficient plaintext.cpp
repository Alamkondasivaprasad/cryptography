#include <stdio.h>
#include <string.h>
int mod26(int x) {
    return (x % 26 + 26) % 26;
}
void matrixMultiply(int key[2][2], int vector[2], int result[2]) {
    result[0] = mod26(key[0][0] * vector[0] + key[0][1] * vector[1]);
    result[1] = mod26(key[1][0] * vector[0] + key[1][1] * vector[1]);
}
int modInverse(int a) {
    for (int i = 1; i < 26; i++) {
        if (mod26(a * i) == 1) {
            return i;
        }
    }
    return -1;
}
int determinant(int key[2][2]) {
    return mod26(key[0][0] * key[1][1] - key[0][1] * key[1][0]);
}
void inverseMatrix(int key[2][2], int inverse[2][2]) {
    int det = determinant(key);
    int invDet = modInverse(det);
    if (invDet == -1) {
        printf("Key matrix is not invertible\n");
        return;
    }
    inverse[0][0] = mod26(invDet * key[1][1]);
    inverse[0][1] = mod26(invDet * -key[0][1]);
    inverse[1][0] = mod26(invDet * -key[1][0]);
    inverse[1][1] = mod26(invDet * key[0][0]);
}
void encrypt(char* plaintext, int key[2][2]) {
    int n = strlen(plaintext);
    int vector[2], result[2];

    printf("Ciphertext: ");
    for (int i = 0; i < n; i += 2) {
        vector[0] = plaintext[i] - 'A';
        vector[1] = plaintext[i + 1] - 'A';
        matrixMultiply(key, vector, result);
        printf("%c%c", result[0] + 'A', result[1] + 'A');
    }
    printf("\n");
}
void decrypt(char* ciphertext, int key[2][2]) {
    int inverse[2][2];
    inverseMatrix(key, inverse);

    int n = strlen(ciphertext);
    int vector[2], result[2];

    printf("Decrypted text: ");
    for (int i = 0; i < n; i += 2) {
        vector[0] = ciphertext[i] - 'A';
        vector[1] = ciphertext[i + 1] - 'A';
        matrixMultiply(inverse, vector, result);
        printf("%c%c", result[0] + 'A', result[1] + 'A');
    }
    printf("\n");
}

int main() {
    int key[2][2] = {
        {9, 4},
        {5, 7}
    };

    char plaintext[] = "HELP";
    printf("Plaintext: %s\n", plaintext);
    encrypt(plaintext, key);
    char ciphertext[] = "BFKU";
    printf("Ciphertext: %s\n", ciphertext);
    decrypt(ciphertext, key);
    return 0;
}

