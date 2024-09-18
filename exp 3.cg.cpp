#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5
void createMatrix(char keyword[], char matrix[SIZE][SIZE]) {
    int freq[26] = {0};
    int len = strlen(keyword);
    int k = 0;

    for (int i = 0; i < len; i++) {
        char ch = toupper(keyword[i]);
        if (ch == 'J') ch = 'I'; 
        if (isalpha(ch) && !freq[ch - 'A']) {
            matrix[k / SIZE][k % SIZE] = ch;
            freq[ch - 'A'] = 1;
            k++;
        }
    }

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue;
        if (!freq[ch - 'A']) {
            matrix[k / SIZE][k % SIZE] = ch;
            k++;
        }
    }
}
void formatPlaintext(char plaintext[], char formatted[]) {
    int len = strlen(plaintext);
    int j = 0;

    for (int i = 0; i < len; i++) {
        if (plaintext[i] == 'J') plaintext[i] = 'I';
        if (isalpha(plaintext[i])) {
            formatted[j++] = toupper(plaintext[i]);
            if (i < len - 1 && plaintext[i] != plaintext[i + 1] && isalpha(plaintext[i + 1])) {
                formatted[j++] = toupper(plaintext[i + 1]);
                i++;
            } else {
                formatted[j++] = 'X'; 
            }
        }
    }
    formatted[j] = '\0';
}
void encryptDigraph(char digraph[], char matrix[SIZE][SIZE], char encrypted[]) {
    int row1, col1, row2, col2;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == digraph[0]) {
                row1 = i;
                col1 = j;
            }
            if (matrix[i][j] == digraph[1]) {
                row2 = i;
                col2 = j;
            }
        }
    }
    if (row1 == row2) {
        encrypted[0] = matrix[row1][(col1 + 1) % SIZE];
        encrypted[1] = matrix[row2][(col2 + 1) % SIZE];
    } else if (col1 == col2) {
        encrypted[0] = matrix[(row1 + 1) % SIZE][col1];
        encrypted[1] = matrix[(row2 + 1) % SIZE][col2];
    } else {
        encrypted[0] = matrix[row1][col2];
        encrypted[1] = matrix[row2][col1];
    }
    encrypted[2] = '\0';
}

int main() {
    char keyword[100], plaintext[100], formatted[200];
    char matrix[SIZE][SIZE];
    printf("Enter keyword: ");
    
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0'; 
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';
    createMatrix(keyword, matrix);
    formatPlaintext(plaintext, formatted);
    printf("Formatted plaintext: %s\n", formatted);
    printf("Ciphertext: ");
    for (int i = 0; i < strlen(formatted); i += 2) {
        char digraph[2] = {formatted[i], formatted[i + 1]};
        char encrypted[3];
        encryptDigraph(digraph, matrix, encrypted);
        printf("%s", encrypted);
    }
    printf("\n");

    return 0;
}

