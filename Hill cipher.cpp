#include <stdio.h>
#include <string.h>

#define SIZE 2
#define MOD 26
int charToNum(char ch) {
    return ch - 'A';
}
char numToChar(int num) {
    return (num % MOD) + 'A';
}
void multiplyMatrices(int key[SIZE][SIZE], int input[SIZE], int result[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        result[i] = 0;
        for (int j = 0; j < SIZE; j++) {
            result[i] += key[i][j] * input[j];
        }
        result[i] %= MOD;
    }
}

int main() {
    int key[SIZE][SIZE] = {{9, 4}, {5, 7}};
    char plaintext[] = "MEETME";
    int len = strlen(plaintext);
    int messageNumbers[len];
    for (int i = 0; i < len; i++) {
        messageNumbers[i] = charToNum(plaintext[i]);
    }
    printf("Ciphertext: ");
    for (int i = 0; i < len; i += SIZE) {
        int input[SIZE] = {messageNumbers[i], messageNumbers[i + 1]};
        int result[SIZE];
        
        multiplyMatrices(key, input, result);
        printf("%c%c", numToChar(result[0]), numToChar(result[1]));
    }
    printf("\n");

    return 0;
}

