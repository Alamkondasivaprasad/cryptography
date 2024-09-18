#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5
char keyMatrix[SIZE][SIZE] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};
void findPosition(char ch, int *row, int *col) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (keyMatrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void formatText(char message[], char formattedText[]) {
    int i, j = 0;
    int len = strlen(message);
    for (i = 0; i < len; i++) {
        if (message[i] != ' ') {
            formattedText[j] = toupper(message[i]);
            if (formattedText[j] == 'J') {
                formattedText[j] = 'I';
            }
            j++;
        }
    }
    formattedText[j] = '\0'; 
}
void preparePairs(char formattedText[], char pairs[][2], int *numPairs) {
    int i, j = 0;
    int len = strlen(formattedText);
    
    for (i = 0; i < len; i++) {
        pairs[j][0] = formattedText[i];
        
        if (i + 1 < len && formattedText[i] != formattedText[i + 1]) {
            pairs[j][1] = formattedText[i + 1];
            i++;
        } else {
            pairs[j][1] = 'X';  
        }
        
        j++;
    }
    *numPairs = j; 
}
void encryptPlayfair(char pairs[][2], int numPairs, char encryptedText[]) {
    int i, row1, col1, row2, col2;
    for (i = 0; i < numPairs; i++) {
        findPosition(pairs[i][0], &row1, &col1);
        findPosition(pairs[i][1], &row2, &col2);
        
        if (row1 == row2) {
            encryptedText[i * 2] = keyMatrix[row1][(col1 + 1) % SIZE];
            encryptedText[i * 2 + 1] = keyMatrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            encryptedText[i * 2] = keyMatrix[(row1 + 1) % SIZE][col1];
            encryptedText[i * 2 + 1] = keyMatrix[(row2 + 1) % SIZE][col2];
        } else {
            encryptedText[i * 2] = keyMatrix[row1][col2];
            encryptedText[i * 2 + 1] = keyMatrix[row2][col1];
        }
    }
    encryptedText[numPairs * 2] = '\0';  
}

int main() {
    char message[] = "Must see you over Cadogan West. Coming at once.";
    char formattedText[100], encryptedText[100];
    char pairs[50][2];  
    int numPairs, i;
    formatText(message, formattedText);
    preparePairs(formattedText, pairs, &numPairs);
    encryptPlayfair(pairs, numPairs, encryptedText);
    printf("Encrypted Message: %s\n", encryptedText);
    
    return 0;
}

