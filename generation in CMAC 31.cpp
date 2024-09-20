#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define BLOCK_SIZE 16 
#define ZERO_BLOCK_SIZE (BLOCK_SIZE / 8)

void left_shift(uint8_t *input, uint8_t *output) {
    uint8_t carry = 0;
    for (int i = BLOCK_SIZE - 1; i >= 0; i--) {
        output[i] = (input[i] << 1) | carry;
        carry = (input[i] & 0x80) ? 1 : 0; 
    }
    if (carry) {
        if (BLOCK_SIZE == 16) { 
            output[BLOCK_SIZE - 1] ^= 0x87;
        } else if (BLOCK_SIZE == 8) { 
            output[BLOCK_SIZE - 1] ^= 0x1B;
        }
    }
}

void generate_subkeys(uint8_t *k1, uint8_t *k2) {
    uint8_t zero_block[BLOCK_SIZE] = {0};
    uint8_t temp[BLOCK_SIZE];
    memcpy(temp, zero_block, BLOCK_SIZE); 
    left_shift(temp, k1);
    left_shift(k1, k2);
}

void print_bytes(const char *label, const uint8_t *data) {
    printf("%s: ", label);
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x ", data[i]);
    }
    printf("\n");
}

int main() {
    uint8_t k1[BLOCK_SIZE] = {0};
    uint8_t k2[BLOCK_SIZE] = {0};

    generate_subkeys(k1, k2);
    
    print_bytes("Subkey K1", k1);
    print_bytes("Subkey K2", k2);

    return 0;
}

