#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>

#define DSA_K_LIMIT 100 
#define MESSAGE_SIZE 32 
uint32_t generate_random_k() {
    return rand() % DSA_K_LIMIT + 1; 
}
void dsa_sign(const char *message, uint32_t *r, uint32_t *s) {
    uint32_t k = generate_random_k(); 
    *r = k % 20; 
    *s = (k + strlen(message)) % 20; 
}
void rsa_sign(const char *message, uint32_t *signature) {
    *signature = (uint32_t)strlen(message) % 20; 
}

int main() {
    srand(time(NULL)); 

    const char *message = "Hello, this is a test message.";
    uint32_t dsa_r1, dsa_s1, dsa_r2, dsa_s2;
    uint32_t rsa_signature1, rsa_signature2;
    dsa_sign(message, &dsa_r1, &dsa_s1);
    dsa_sign(message, &dsa_r2, &dsa_s2);
    rsa_sign(message, &rsa_signature1);
    rsa_sign(message, &rsa_signature2);
    printf("DSA Signatures:\n");
    printf("Signature 1: (r: %u, s: %u)\n", dsa_r1, dsa_s1);
    printf("Signature 2: (r: %u, s: %u)\n", dsa_r2, dsa_s2);
    
    printf("\nRSA Signatures:\n");
    printf("Signature 1: %u\n", rsa_signature1);
    printf("Signature 2: %u\n", rsa_signature2);

    return 0;
}

