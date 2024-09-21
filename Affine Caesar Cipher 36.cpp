#include <stdio.h>
#include <ctype.h>
#include <string.h> 

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; 
}

char affineEncrypt(char p, int a, int b) {
    if (!isalpha(p)) {
        return p; 
    }

    p = toupper(p) - 'A'; 
    int C = (a * p + b) % 26; 
    return C + 'A';          
}

char affineDecrypt(char C, int a, int b) {
    if (!isalpha(C)) {
        return C;
    }

    C = toupper(C) - 'A'; 
    int a_inv = modInverse(a, 26); 
    if (a_inv == -1) {
        printf("Decryption impossible, a and 26 are not coprime.\n");
        return C;
    }
    int P = (a_inv * (C - b + 26)) % 26; 
    return P + 'A';                      
}

int main() {
    char plaintext[] = "HELLO AFFINE CIPHER";
    int a = 5; 
    int b = 8; 
    char ciphertext[100], decryptedtext[100];

    printf("Plaintext: %s\n", plaintext);
    for (int i = 0; plaintext[i] != '\0'; i++) {
        ciphertext[i] = affineEncrypt(plaintext[i], a, b);
    }
    ciphertext[strlen(plaintext)] = '\0';  
    printf("Ciphertext: %s\n", ciphertext);
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        decryptedtext[i] = affineDecrypt(ciphertext[i], a, b);
    }
    decryptedtext[strlen(ciphertext)] = '\0';  
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}

