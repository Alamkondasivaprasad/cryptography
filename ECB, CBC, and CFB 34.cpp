#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 8  // Block size is 64 bits (8 bytes)

// XOR operation (used for simplicity)
void xorBlock(unsigned char *a, unsigned char *b, unsigned char *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = a[i] ^ b[i];
    }
}

// Padding function
void padBlock(unsigned char *block, int length) {
    int padValue = BLOCK_SIZE - length;
    for (int i = length; i < BLOCK_SIZE; i++) {
        block[i] = (i == length) ? 0x80 : 0x00;  // 1 followed by zeros
    }
}

// ECB Mode Encryption
void ECB_encrypt(unsigned char *plaintext, unsigned char *key, unsigned char *ciphertext, int length) {
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        xorBlock(&plaintext[i], key, &ciphertext[i]);
    }
}

// CBC Mode Encryption
void CBC_encrypt(unsigned char *plaintext, unsigned char *key, unsigned char *ciphertext, unsigned char *iv, int length) {
    unsigned char temp[BLOCK_SIZE];

    for (int i = 0; i < length; i += BLOCK_SIZE) {
        xorBlock(&plaintext[i], iv, temp);     // XOR with IV (or previous block)
        xorBlock(temp, key, &ciphertext[i]);   // Encrypt block
        memcpy(iv, &ciphertext[i], BLOCK_SIZE); // Update IV
    }
}

// CFB Mode Encryption
void CFB_encrypt(unsigned char *plaintext, unsigned char *key, unsigned char *ciphertext, unsigned char *iv, int length) {
    unsigned char temp[BLOCK_SIZE];

    for (int i = 0; i < length; i += BLOCK_SIZE) {
        xorBlock(iv, key, temp);              // Encrypt IV
        xorBlock(&plaintext[i], temp, &ciphertext[i]); // XOR with plaintext
        memcpy(iv, &ciphertext[i], BLOCK_SIZE); // Update IV
    }
}

int main() {
    unsigned char plaintext[] = "This is a test message";  // Plaintext (must be a multiple of BLOCK_SIZE)
    unsigned char key[BLOCK_SIZE] = "secretK";             // Key (fixed size 8 bytes)
    unsigned char iv[BLOCK_SIZE] = "initialV";             // IV (initialization vector)
    unsigned char ciphertext[BLOCK_SIZE * 3];
    unsigned char padded_plaintext[BLOCK_SIZE * 3];        // Buffer for padded plaintext
    int plaintext_length = strlen((char *)plaintext);
    int padded_length = ((plaintext_length / BLOCK_SIZE) + 1) * BLOCK_SIZE;

    // Padding the plaintext
    memcpy(padded_plaintext, plaintext, plaintext_length);
    padBlock(padded_plaintext + plaintext_length, plaintext_length % BLOCK_SIZE);

    printf("Original Plaintext: %s\n", plaintext);

    // ECB Encryption
    printf("\n--- ECB Mode ---\n");
    ECB_encrypt(padded_plaintext, key, ciphertext, padded_length);
    printf("Ciphertext (ECB): ");
    for (int i = 0; i < padded_length; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");

    // CBC Encryption
    printf("\n--- CBC Mode ---\n");
    memcpy(iv, "initialV", BLOCK_SIZE);  // Reset IV
    CBC_encrypt(padded_plaintext, key, ciphertext, iv, padded_length);
    printf("Ciphertext (CBC): ");
    for (int i = 0; i < padded_length; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");

    // CFB Encryption
    printf("\n--- CFB Mode ---\n");
    memcpy(iv, "initialV", BLOCK_SIZE);  // Reset IV
    CFB_encrypt(padded_plaintext, key, ciphertext, iv, padded_length);
    printf("Ciphertext (CFB): ");
    for (int i = 0; i < padded_length; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");

    return 0;
}

