#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define ALPHABET_SIZE 26
#define MAX_TEXT_LENGTH 1024
#define TOP_PLAINTEXTS 10
const double english_freq[ALPHABET_SIZE] = {
    0.08167, 0.01492, 0.02782, 0.04253, 0.12702,
    0.02228, 0.02015, 0.06094, 0.06966, 0.00153,
    0.00772, 0.04025, 0.02406, 0.06749, 0.07507,
    0.01929, 0.00098, 0.05987, 0.06327, 0.09056,
    0.02758, 0.00978, 0.01515, 0.01934, 0.00150,
    0.00772
};
void calculate_frequency(const char *text, int *frequency) {
    while (*text) {
        char ch = tolower(*text++);
        if (isalpha(ch)) {
            frequency[ch - 'a']++;
        }
    }
}
void create_substitution(int *frequency, char *substitution) {
    int sorted_indices[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        sorted_indices[i] = i;
    }
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = 0; j < ALPHABET_SIZE - i - 1; j++) {
            if (frequency[sorted_indices[j]] < frequency[sorted_indices[j + 1]]) {
                int temp = sorted_indices[j];
                sorted_indices[j] = sorted_indices[j + 1];
                sorted_indices[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        substitution[sorted_indices[i]] = 'a' + i;
    }
}
void decrypt(const char *ciphertext, const char *substitution, char *plaintext) {
    while (*ciphertext) {
        char ch = tolower(*ciphertext++);
        if (isalpha(ch)) {
            *plaintext++ = substitution[ch - 'a'];
        } else {
            *plaintext++ = ch; 
        }
    }
    *plaintext = '\0';
}
void generate_plaintexts(const char *ciphertext, int top_n) {
    int frequency[ALPHABET_SIZE] = {0};
    calculate_frequency(ciphertext, frequency);

    char substitution[ALPHABET_SIZE] = {0};
    create_substitution(frequency, substitution);

    char plaintext[MAX_TEXT_LENGTH];
    decrypt(ciphertext, substitution, plaintext);
    printf("Possible plaintexts:\n");
    for (int i = 0; i < top_n; i++) {
        printf("%d: %s\n", i + 1, plaintext);
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

