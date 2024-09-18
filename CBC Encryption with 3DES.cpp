#include <stdio.h>
#include <stdint.h>
uint64_t DES_Encrypt(uint64_t block, uint64_t key) {
    return block; 
}

uint64_t DES_Decrypt(uint64_t block, uint64_t key) {
    return block; 
}

uint64_t TripleDES_Encrypt(uint64_t block, uint64_t key1, uint64_t key2, uint64_t key3) {
    return DES_Encrypt(DES_Decrypt(DES_Encrypt(block, key1), key2), key3);
}

void CBC_Encrypt(uint64_t plaintext[], uint64_t ciphertext[], uint64_t iv, uint64_t key1, uint64_t key2, uint64_t key3, int n) {
    uint64_t prev_block = iv;
    for (int i = 0; i < n; i++) {
        uint64_t xor_block = plaintext[i] ^ prev_block;  
        ciphertext[i] = TripleDES_Encrypt(xor_block, key1, key2, key3); 
        prev_block = ciphertext[i];  
    }
}

int main() {
    uint64_t key1 = 0x0123456789ABCDEF, key2 = 0x23456789ABCDEF01, key3 = 0x3456789ABCDEF012;
    uint64_t iv = 0xAABBCCDDEEFF0011;
    uint64_t plaintext[] = {0x1111111111111111, 0x2222222222222222};  
    uint64_t ciphertext[2]; 

    CBC_Encrypt(plaintext, ciphertext, iv, key1, key2, key3, 2);  

    printf("Ciphertext: %lx %lx\n", ciphertext[0], ciphertext[1]); 

    return 0;
}

