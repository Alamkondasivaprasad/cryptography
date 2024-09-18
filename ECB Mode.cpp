#include <stdio.h>
#include <stdint.h>
uint64_t Block_Encrypt(uint64_t block, uint64_t key) {
    return block ^ key;  
}

void ECB_Encrypt(uint64_t plaintext[], uint64_t ciphertext[], uint64_t key, int n) {
    for (int i = 0; i < n; i++) {
        ciphertext[i] = Block_Encrypt(plaintext[i], key);  
    }
}

int main() {
    uint64_t key = 0x0123456789ABCDEF;
    uint64_t plaintext[] = {0x1111111111111111, 0x2222222222222222}; 
    uint64_t ciphertext[2];

    ECB_Encrypt(plaintext, ciphertext, key, 2);  

    printf("Ciphertext: %lx %lx\n", ciphertext[0], ciphertext[1]);  

    return 0;
}

