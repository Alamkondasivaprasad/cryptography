#include <stdio.h>
#include <math.h>
unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
unsigned long long modInverse(unsigned long long e, unsigned long long phi) {
    unsigned long long d = 1;
    while ((e * d) % phi != 1) {
        d++;
    }
    return d;
}
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

int main() {
    unsigned long long p = 61;  
    unsigned long long q = 53;  
    unsigned long long n = p * q; 
    unsigned long long phi = (p - 1) * (q - 1); 
    unsigned long long e = 17; 
    unsigned long long d = modInverse(e, phi);

    printf("Public Key (e, n): (%llu, %llu)\n", e, n);
    printf("Private Key (d, n): (%llu, %llu)\n", d, n);
    unsigned long long message = 42;
    printf("Original Message: %llu\n", message);
    unsigned long long encrypted = modExp(message, e, n);
    printf("Encrypted Message: %llu\n", encrypted);
    unsigned long long decrypted = modExp(encrypted, d, n);
    printf("Decrypted Message: %llu\n", decrypted);
    printf("Bob leaks his private key!\n");
    unsigned long long new_e = 23; 
    unsigned long long new_d = modInverse(new_e, phi); 

    printf("New Public Key (e, n): (%llu, %llu)\n", new_e, n);
    printf("New Private Key (d, n): (%llu, %llu)\n", new_d, n);
    return 0;
}

