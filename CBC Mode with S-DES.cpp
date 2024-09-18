#include <stdio.h>
#include <stdint.h>

#define BLOCK_SIZE 8  
uint8_t XOR(uint8_t a, uint8_t b) {
    return a ^ b;
}
uint8_t S_DES_Encrypt(uint8_t plaintext, uint8_t key) {
    return plaintext ^ key; 
}

uint8_t S_DES_Decrypt(uint8_t ciphertext, uint8_t key) {
    return ciphertext ^ key; 
}
void CBC_Encrypt(uint8_t plaintext[], uint8_t ciphertext[], uint8_t iv, uint8_t key, int n) {
    uint8_t prev_block = iv;
    for (int i = 0; i < n; i++) {
        uint8_t xor_block = XOR(plaintext[i], prev_block);  
        ciphertext[i] = S_DES_Encrypt(xor_block, key);  
        prev_block = ciphertext[i];  
    }
}
void CBC_Decrypt(uint8_t ciphertext[], uint8_t decrypted[], uint8_t iv, uint8_t key, int n) {
    uint8_t prev_block = iv;
    for (int i = 0; i < n; i++) {
        uint8_t decrypted_block = S_DES_Decrypt(ciphertext[i], key); 
        decrypted[i] = XOR(decrypted_block, prev_block);  
        prev_block = ciphertext[i];  
    }
}

int main() {
    uint8_t iv = 0xAA;  
    uint8_t plaintext[] = {0x01, 0x23};  
    uint8_t key = 0x7D;  
    uint8_t ciphertext[2], decrypted[2];
    CBC_Encrypt(plaintext, ciphertext, iv, key, 2);
    printf("Encrypted ciphertext: %02X %02X\n", ciphertext[0], ciphertext[1]);
    CBC_Decrypt(ciphertext, decrypted, iv, key, 2);
    printf("Decrypted plaintext: %02X %02X\n", decrypted[0], decrypted[1]);

    return 0;
}

