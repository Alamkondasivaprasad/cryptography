#include <stdio.h>
#include <string.h>
#define ALPHABET_SIZE 26
int char_to_num(char c) {
    return c - 'a';
}
char num_to_char(int n) {
    return n + 'a';
}
void encrypt_vigenere(char *plaintext, int *key, int key_length, char *ciphertext) {
    int length = strlen(plaintext);
    for (int i = 0; i < length; i++) {
        int pt_val = char_to_num(plaintext[i]);
        int key_val = key[i % key_length];
        int encrypted_val = (pt_val + key_val) % ALPHABET_SIZE;
        ciphertext[i] = num_to_char(encrypted_val);
    }
    ciphertext[length] = '\0'; 
}

int main() {
    char plaintext[] = "sendmoremoney";
    int key[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    int key_length = sizeof(key) / sizeof(key[0]);
    char ciphertext[sizeof(plaintext)];
    
    printf("Plaintext: %s\n", plaintext);
    
    encrypt_vigenere(plaintext, key, key_length, ciphertext);
    
    printf("Ciphertext: %s\n", ciphertext);
    return 0;
}

