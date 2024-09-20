#include <stdio.h>
#include <math.h>
unsigned long long modExp(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}
void precompute_attack(unsigned long long e, unsigned long long n, unsigned long long encrypted_message) {
    for (int i = 0; i < 26; i++) {
        unsigned long long ciphertext = modExp(i, e, n);
        if (ciphertext == encrypted_message) {
            printf("Decrypted Character: %c (Integer value: %d)\n", 'A' + i, i);
            return;
        }
    }
    printf("No match found!\n");
}

int main() {
    unsigned long long p = 61;
    unsigned long long q = 53;
    unsigned long long n = p * q;
    unsigned long long phi = (p - 1) * (q - 1); 
    unsigned long long e = 17;
    char message = 'H'; 
    unsigned long long plaintext = message - 'A'; 

    printf("Original Message: %c (Integer value: %llu)\n", message, plaintext);
    unsigned long long encrypted_message = modExp(plaintext, e, n);
    printf("Encrypted Message: %llu\n", encrypted_message);
    printf("Simulating attack...\n");
    precompute_attack(e, n, encrypted_message);

    return 0;
}

