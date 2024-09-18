#include <stdio.h>
#include <stdint.h>

#define BLOCK_SIZE 8  
#define NUM_BLOCKS 3  
uint8_t XOR(uint8_t a, uint8_t b) {
    return a ^ b;
}
uint8_t S_DES_Encrypt(uint8_t block, uint8_t key) {
    return block ^ key;  
}
void CTR_Encrypt(uint8_t plaintext[], uint8_t ciphertext[], uint8_t counter, uint8_t key, int n) {
    for (int i = 0; i < n; i++) {
        uint8_t encrypted_counter = S_DES_Encrypt(counter + i, key); 
        ciphertext[i] = XOR(plaintext[i], encrypted_counter); 
    }
}
void CTR_Decrypt(uint8_t ciphertext[], uint8_t plaintext[], uint8_t counter, uint8_t key, int n) {
    CTR_Encrypt(ciphertext, plaintext, counter, key, n);  
}

int main() {
    uint8_t key = 0x7D;  
    uint8_t counter = 0x00;  
    uint8_t plaintext[] = {0x01, 0x10, 0x04};  
    uint8_t ciphertext[NUM_BLOCKS], decrypted[NUM_BLOCKS];
    CTR_Encrypt(plaintext, ciphertext, counter, key, NUM_BLOCKS);
    printf("Encrypted ciphertext: %02X %02X %02X\n", ciphertext[0], ciphertext[1], ciphertext[2]);
    CTR_Decrypt(ciphertext, decrypted, counter, key, NUM_BLOCKS);
    printf("Decrypted plaintext: %02X %02X %02X\n", decrypted[0], decrypted[1], decrypted[2]);

    return 0;
}

