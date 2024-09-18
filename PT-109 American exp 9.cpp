#include <stdio.h>
#include <string.h>
#define SIZE 5

void generateKeyMatrix(char key[], char keyMatrix[SIZE][SIZE]) {
    int alpha[26] = {0}, i, k = 0;
    for (i = 0; key[i]; i++) if (key[i] != 'J' && !alpha[key[i] - 'A']) 
        keyMatrix[k / SIZE][k % SIZE] = key[i], alpha[key[i] - 'A'] = 1, k++;
    for (i = 0; i < 26; i++) if (i != 'J' - 'A' && !alpha[i]) 
        keyMatrix[k / SIZE][k % SIZE] = 'A' + i, k++;
}

void findPosition(char ch, char keyMatrix[SIZE][SIZE], int *row, int *col) {
    for (int i = 0; i < SIZE; i++) for (int j = 0; j < SIZE; j++) 
        if (keyMatrix[i][j] == ch) *row = i, *col = j;
}

void decryptPlayfair(char cipherText[], char keyMatrix[SIZE][SIZE], char decryptedText[]) {
    int row1, col1, row2, col2;
    for (int i = 0; i < strlen(cipherText); i += 2) {
        findPosition(cipherText[i], keyMatrix, &row1, &col1);
        findPosition(cipherText[i + 1], keyMatrix, &row2, &col2);
        decryptedText[i] = row1 == row2 ? keyMatrix[row1][(col1 - 1 + SIZE) % SIZE] :
                          col1 == col2 ? keyMatrix[(row1 - 1 + SIZE) % SIZE][col1] :
                                         keyMatrix[row1][col2];
        decryptedText[i + 1] = row1 == row2 ? keyMatrix[row2][(col2 - 1 + SIZE) % SIZE] :
                             col1 == col2 ? keyMatrix[(row2 - 1 + SIZE) % SIZE][col2] :
                                            keyMatrix[row2][col1];
    }
    decryptedText[strlen(cipherText)] = '\0';
}

int main() {
    char key[] = "PLAYFAIREXAMPLE", cipherText[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONEYC", decryptedText[100];
    char keyMatrix[SIZE][SIZE]; 
    generateKeyMatrix(key, keyMatrix);
    decryptPlayfair(cipherText, keyMatrix, decryptedText);
    printf("Decrypted Message: %s\n", decryptedText);
    return 0;
}

