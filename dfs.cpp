#include <stdio.h>
#include <string.h>
#define BLOCK_SIZE 100
#define KEY_SIZE 8
int S[4][16] = {
    {14, 4, 13, 1, 2, 7, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
    {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 9, 0, 1, 3, 13, 8},
    {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
    {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
};
void des_round(unsigned char *L, unsigned char *R, unsigned char *key) {
    unsigned char temp[BLOCK_SIZE / 2];
    for (int i = 0; i < BLOCK_SIZE / 2; i++) temp[i] = R[i] ^ key[i];
    for (int i = 0; i < 4; i++) temp[i] = S[i][temp[i] % 16];
    memcpy(R, L, BLOCK_SIZE / 2);
    memcpy(L, temp, BLOCK_SIZE / 2);
}
void des_encrypt(unsigned char *data, unsigned char *key) {
    unsigned char L[BLOCK_SIZE / 2], R[BLOCK_SIZE / 2];
    memcpy(L, data, BLOCK_SIZE / 2);
    memcpy(R, data + BLOCK_SIZE / 2, BLOCK_SIZE / 2);
    for (int i = 0; i < 16; i++) des_round(L, R, key);
    memcpy(data, L, BLOCK_SIZE / 2);
    memcpy(data + BLOCK_SIZE / 2, R, BLOCK_SIZE / 2);
}
int main() {
    unsigned char key[KEY_SIZE] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xCD, 0xEF, 0x0F};
    unsigned char data[BLOCK_SIZE] = "EFGH";
    printf("Plaintext: %s\n", data);
    des_encrypt(data, key);
    printf("Ciphertext: ");
    for (int i = 0; i < BLOCK_SIZE; i++) printf("%02X ", data[i]);
    printf("\n");
    return 0;
}

