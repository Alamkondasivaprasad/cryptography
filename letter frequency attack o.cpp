#include <stdio.h>
#include <string.h>
#include <ctype.h>
double englishFreq[26] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153,
    0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056,
    2.758, 0.978, 2.360, 0.150, 1.974, 0.074
};
double calculateScore(char* plaintext, int length) {
    int letterCount[26] = {0};
    int totalLetters = 0;
    for (int i = 0; i < length; i++) {
        if (isalpha(plaintext[i])) {
            int index = toupper(plaintext[i]) - 'A';
            letterCount[index]++;
            totalLetters++;
        }
    }
    double score = 0.0;
    for (int i = 0; i < 26; i++) {
        double expected = englishFreq[i] * totalLetters / 100.0;
        score += ((letterCount[i] - expected) * (letterCount[i] - expected)) / expected;
    }

    return score;
}
void decryptWithShift(char* ciphertext, char* plaintext, int shift, int length) {
    for (int i = 0; i < length; i++) {
        if (isalpha(ciphertext[i])) {
            int base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = (ciphertext[i] - base - shift + 26) % 26 + base;
        } else {
            plaintext[i] = ciphertext[i]; 
        }
    }
    plaintext[length] = '\0'; 
}
void letterFrequencyAttack(char* ciphertext, int topN) {
    int length = strlen(ciphertext);
    char possiblePlaintext[26][1000];  
    double scores[26]; 
    for (int shift = 0; shift < 26; shift++) {
        decryptWithShift(ciphertext, possiblePlaintext[shift], shift, length);
        scores[shift] = calculateScore(possiblePlaintext[shift], length);
    }
    for (int i = 0; i < 25; i++) {
        for (int j = i + 1; j < 26; j++) {
            if (scores[i] > scores[j]) {
                double tempScore = scores[i];
                scores[i] = scores[j];
                scores[j] = tempScore;
                
                char tempText[1000];
                strcpy(tempText, possiblePlaintext[i]);
                strcpy(possiblePlaintext[i], possiblePlaintext[j]);
                strcpy(possiblePlaintext[j], tempText);
            }
        }
    }
    printf("Top %d possible plaintexts:\n", topN);
    for (int i = 0; i < topN; i++) {
        printf("%d. %s (Score: %.2f)\n", i + 1, possiblePlaintext[i], scores[i]);
    }
}

int main() {
    char ciphertext[] = "KHOOR ZRUOG";  
    int topN = 10;
    letterFrequencyAttack(ciphertext, topN);

    return 0;
}

