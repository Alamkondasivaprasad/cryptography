#include <stdio.h>
#include <string.h>
#include <ctype.h>
void polyalphabeticEncrypt(char* plaintext, char* key) {
    int textLength = strlen(plaintext);
    int keyLength = strlen(key);
    for (int i = 0, j = 0; i < textLength; i++) {
        char ch = plaintext[i];
        if (isupper(ch)) {
            plaintext[i] = ((ch - 'A') + (toupper(key[j % keyLength]) - 'A')) % 26 + 'A';
            j++;
        }
        else if (islower(ch)) {
            plaintext[i] = ((ch - 'a') + (tolower(key[j % keyLength]) - 'a')) % 26 + 'a';
            j++;
        }
    }
}

int main() {
    char plaintext[100], key[100];
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; 
    polyalphabeticEncrypt(plaintext, key);
    printf("Encrypted text: %s\n", plaintext);
    
    return 0;
}

