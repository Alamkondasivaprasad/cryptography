#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define ALPHABET_SIZE 26
#define MAX_TEXT_LENGTH 1024
#define TOP_PLAINTEXTS 10
void calculate_frequency(const char *text, int *frequency) {
    for (int i = 0; text[i] != '\0'; i++) {
        char ch = tolower(text[i]);
        if (isalpha(ch)) {
            frequency[ch - 'a']++;
        }
    }
}
void decrypt(const char *ciphertext, int shift, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char ch = ciphertext[i];
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            plaintext[i] = (ch - base - shift + ALPHABET_SIZE) % ALPHABET_SIZE + base;
        } else {
            plaintext[i] = ch; 
        }
    }
    plaintext[strlen(ciphertext)] = '\0'; 
}
void generate_plaintexts(const char *ciphertext, int top_n) {
    int frequency[ALPHABET_SIZE] = {0};
    calculate_frequency(ciphertext, frequency);
    int most_common_letter = 4; 
    char possible_plaintexts[TOP_PLAINTEXTS][MAX_TEXT_LENGTH];

    for (int i = 0; i < top_n; i++) {
        int shift = (most_common_letter - (i % ALPHABET_SIZE) + ALPHABET_SIZE) % ALPHABET_SIZE;
        decrypt(ciphertext, shift, possible_plaintexts[i]);
        printf("Possible plaintext %d: %s\n", i + 1, possible_plaintexts[i]);
    }
}

int main() {
    char ciphertext[MAX_TEXT_LENGTH];
    int top_n;
    printf("Enter the ciphertext: ");
    fgets(ciphertext, MAX_TEXT_LENGTH, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = 0; 
    printf("How many possible plaintexts do you want to see? (up to %d): ", TOP_PLAINTEXTS);
    scanf("%d", &top_n);
    if (top_n > TOP_PLAINTEXTS) {
        top_n = TOP_PLAINTEXTS;
    }
    generate_plaintexts(ciphertext, top_n);

    return 0;
}

