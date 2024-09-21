#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26
const char english_freq[] = "etaoinshrdlcumwfgypbvkjxqz";
typedef struct {
    char letter;
    float frequency;
} LetterFreq;
void countFrequencies(const char *ciphertext, LetterFreq freqs[]) {
    int count[ALPHABET_SIZE] = {0};
    int total = 0;
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            count[ciphertext[i] - 'a']++;
            total++;
        } else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            count[ciphertext[i] - 'A']++;
            total++;
        }
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freqs[i].letter = 'a' + i;
        freqs[i].frequency = (float)count[i] / total;
    }
}
int compareFreq(const void *a, const void *b) {
    LetterFreq *fa = (LetterFreq *)a;
    LetterFreq *fb = (LetterFreq *)b;
    return (fb->frequency > fa->frequency) - (fb->frequency < fa->frequency);
}
void decrypt(const char *ciphertext, const char *mapping, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = mapping[ciphertext[i] - 'a'];
        } else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = mapping[ciphertext[i] - 'A'] - 32;
        } else {
            plaintext[i] = ciphertext[i]; 
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}
int main() {
    char ciphertext[1000], plaintext[1000];
    LetterFreq freqs[ALPHABET_SIZE];
    int top_n;

    printf("Enter the ciphertext:\n");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; 

    printf("How many top possible plaintexts would you like to see? ");
    scanf("%d", &top_n);
    countFrequencies(ciphertext, freqs);
    qsort(freqs, ALPHABET_SIZE, sizeof(LetterFreq), compareFreq);
    printf("\nTop %d possible plaintexts:\n", top_n);
    for (int i = 0; i < top_n; i++) {
        char mapping[ALPHABET_SIZE];
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            mapping[freqs[j].letter - 'a'] = english_freq[(j + i) % ALPHABET_SIZE];
        }
        decrypt(ciphertext, mapping, plaintext);
        printf("%d: %s\n", i + 1, plaintext);
    }

    return 0;
}

