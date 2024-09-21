#include <stdio.h>
#include <string.h>
void xorOperation(unsigned char *a, unsigned char *b, int length) {
    for (int i = 0; i < length; i++) {
        a[i] ^= b[i];
    }
}
void DES_encrypt(unsigned char *input, unsigned char *key, unsigned char *output) {
    unsigned char temp[8];
    memcpy(temp, input, 8);
    
    for (int i = 0; i < 8; i++) {
        temp[i] ^= key[i];  
    }
    
    memcpy(output, temp, 8);
}
void DES_decrypt(unsigned char *input, unsigned char *key, unsigned char *output) {
    unsigned char temp[8];
    memcpy(temp, input, 8);
    
    for (int i = 0; i < 8; i++) {
        temp[i] ^= key[i];  
    }
    
    memcpy(output, temp, 8);
}

int main() {
    unsigned char plaintext[8] = "OpenAI!";  
    unsigned char key[8] = "secretK";        
    unsigned char ciphertext[8];
    unsigned char decryptedtext[8];
    printf("Original Plaintext: %s\n", plaintext);
    DES_encrypt(plaintext, key, ciphertext);
    printf("Ciphertext: ");
    for (int i = 0; i < 8; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");
    DES_decrypt(ciphertext, key, decryptedtext);
    printf("Decrypted Text: %s\n", decryptedtext);

    return 0;
}

