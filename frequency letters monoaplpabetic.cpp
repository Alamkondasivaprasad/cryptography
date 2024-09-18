#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26
#define TOP_N 10
const double englishFreq[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153,
    0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.316, 9.056,
    2.758, 0.978, 2.560, 0.150, 1.929, 0.074
};

void calculateFrequency(const char *text, double freq[ALPHABET_SIZE]) {
    int counts[ALPHABET_SIZE] = {0};
    int total = 0;

    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            char ch = toupper(text[i]) - 'A';
            counts[ch]++;
            total++;
        }
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freq[i] = (double)counts[i] / total * 100;
    }
}

void printTopPlaintexts(const char *cipherText, int topN) {
    double freq[ALPHABET_SIZE];
    double sortedFreq[ALPHABET_SIZE];
    int sortedIndices[ALPHABET_SIZE];

    calculateFrequency(cipherText, freq);

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        sortedIndices[i] = i;
        sortedFreq[i] = freq[i];
    }

    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (sortedFreq[i] < sortedFreq[j]) {
                double tempFreq = sortedFreq[i];
                int tempIndex = sortedIndices[i];
                sortedFreq[i] = sortedFreq[j];
                sortedIndices[i] = sortedIndices[j];
                sortedFreq[j] = tempFreq;
                sortedIndices[j] = tempIndex;
            }
        }
    }

    for (int i = 0; i < topN; i++) {
        printf("Possible Plaintext #%d: ", i + 1);
        for (int j = 0; cipherText[j]; j++) {
            if (isalpha(cipherText[j])) {
                char ch = toupper(cipherText[j]) - 'A';
                char mappedCh = 'A' + sortedIndices[ch];
                printf("%c", mappedCh);
            } else {
                printf("%c", cipherText[j]);
            }
        }
        printf("\n");
    }
}

int main() {
    char cipherText[] = "LIPPS ASVPH"; 
    int topN = TOP_N;

    printf("Top %d possible plaintexts:\n", topN);
    printTopPlaintexts(cipherText, topN);

    return 0;
}

