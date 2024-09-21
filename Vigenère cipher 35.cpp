#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_TEXT_LENGTH 100
void generateRandomKey(int *key, int length) {
    for (int i = 0; i < length; i++) {
        key[i] = rand() % 26;  
    }
}
void encryptVigenere(char *plaintext, int *key, char *ciphertext, int length) {
    for (int i = 0; i < length; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = ((plaintext[i] - 'A' + key[i]) % 26) + 'A';
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[length] = '\0'; 
}
void decryptVigenere(char *ciphertext, int *key, char *plaintext, int length) {
    for (int i = 0; i < length; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = ((ciphertext[i] - 'A' - key[i] + 26) % 26) + 'A';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[length] = '\0'; 
}

int main() {
    char plaintext[MAX_TEXT_LENGTH], ciphertext[MAX_TEXT_LENGTH];
    int key[MAX_TEXT_LENGTH];
    int length;
    srand(time(0));
    printf("Enter plaintext (uppercase letters only): ");
    fgets(plaintext, sizeof(plaintext), stdin);
    length = strlen(plaintext) - 1;  
    plaintext[length] = '\0';        
    generateRandomKey(key, length);
    printf("Random key (shifts): ");
    for (int i = 0; i < length; i++) {
        printf("%d ", key[i]);
    }
    printf("\n");
    encryptVigenere(plaintext, key, ciphertext, length);
    printf("Ciphertext: %s\n", ciphertext);
    decryptVigenere(ciphertext, key, plaintext, length);
    printf("Decrypted Plaintext: %s\n", plaintext);

    return 0;
}

