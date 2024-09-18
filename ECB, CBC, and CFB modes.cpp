#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8  
uint64_t Block_Encrypt(uint64_t block, uint64_t key) {
    return block ^ key;
}

void Pad_Plaintext(uint64_t *plaintext, int *n) {
    int pad_len = BLOCK_SIZE - (*n % BLOCK_SIZE);
    if (pad_len > 0) {
        plaintext[*n / 8] |= (1ULL << (pad_len * 8 - 1)); 
        *n += pad_len; 
    }
}

void ECB_Encrypt(uint64_t plaintext[], uint64_t ciphertext[], uint64_t key, int n) {
    for (int i = 0; i < n; i++) {
        ciphertext[i] = Block_Encrypt(plaintext[i], key); 
    }
}

void CBC_Encrypt(uint64_t plaintext[], uint64_t ciphertext[], uint64_t iv, uint64_t key, int n) {
    uint64_t prev_block = iv;
    for (int i = 0; i < n; i++) {
        uint64_t xor_block = plaintext[i] ^ prev_block;  
        ciphertext[i] = Block_Encrypt(xor_block, key);  
        prev_block = ciphertext[i];  
    }
}

void CFB_Encrypt(uint64_t plaintext[], uint64_t ciphertext[], uint64_t iv, uint64_t key, int n) {
    uint64_t prev_block = iv;
    for (int i = 0; i < n; i++) {
        uint64_t encrypted_iv = Block_Encrypt(prev_block, key);  
        ciphertext[i] = plaintext[i] ^ encrypted_iv;  
        prev_block = ciphertext[i]; 
    }
}

int main() {
    uint64_t key = 0x0123456789ABCDEF;
    uint64_t iv = 0xAABBCCDDEEFF0011;
    uint64_t plaintext[] = {0x1111111111111111, 0x2222222222222222};  
    uint64_t ciphertext[2];

    int n = sizeof(plaintext) * 8;  
    Pad_Plaintext(plaintext, &n);  
    ECB_Encrypt(plaintext, ciphertext, key, 2);
    printf("ECB Ciphertext: %lx %lx\n", ciphertext[0], ciphertext[1]);
    CBC_Encrypt(plaintext, ciphertext, iv, key, 2);
    printf("CBC Ciphertext: %lx %lx\n", ciphertext[0], ciphertext[1]);
    CFB_Encrypt(plaintext, ciphertext, iv, key, 2);
    printf("CFB Ciphertext: %lx %lx\n", ciphertext[0], ciphertext[1]);

    return 0;
}

