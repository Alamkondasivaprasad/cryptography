#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 16 
void block_cipher(uint8_t *block, const uint8_t *key) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] ^= key[i];
    }
}
void cbc_mac(const uint8_t *key, const uint8_t *message, size_t message_len, uint8_t *mac) {
    uint8_t iv[BLOCK_SIZE] = {0}; 
    uint8_t block[BLOCK_SIZE];
    for (size_t i = 0; i < message_len; i += BLOCK_SIZE) {
        memset(block, 0, BLOCK_SIZE);
        size_t block_len = (i + BLOCK_SIZE <= message_len) ? BLOCK_SIZE : message_len - i;
        memcpy(block, message + i, block_len);
        for (int j = 0; j < BLOCK_SIZE; j++) {
            block[j] ^= iv[j];
        }
        block_cipher(block, key);
        memcpy(iv, block, BLOCK_SIZE);
    }
    memcpy(mac, iv, BLOCK_SIZE);
}

int main() {
    uint8_t key[BLOCK_SIZE] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 
                               0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10};
    uint8_t messageX[BLOCK_SIZE] = {0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 
                                     0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70}; 

    uint8_t mac[BLOCK_SIZE];
    cbc_mac(key, messageX, BLOCK_SIZE, mac);
    
    printf("MAC(T) = ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x ", mac[i]);
    }
    printf("\n");
    uint8_t adversaryMessage[2 * BLOCK_SIZE];
    memcpy(adversaryMessage, messageX, BLOCK_SIZE);
    for (int i = 0; i < BLOCK_SIZE; i++) {
        adversaryMessage[BLOCK_SIZE + i] = messageX[i] ^ mac[i];
    }
    uint8_t adversaryMac[BLOCK_SIZE];
    cbc_mac(key, adversaryMessage, 2 * BLOCK_SIZE, adversaryMac);
    
    printf("MAC for X || (X ? T) = ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x ", adversaryMac[i]);
    }
    printf("\n");

    return 0;
}

