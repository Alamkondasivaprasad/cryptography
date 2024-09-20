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

int main() {
    unsigned long long a = 5;     
    unsigned long long q = 23;    
    unsigned long long x_Alice = 6;  
    unsigned long long x_Bob = 15;   
    unsigned long long A = modExp(a, x_Alice, q);
    printf("Alice sends to Bob: %llu\n", A);
    unsigned long long B = modExp(a, x_Bob, q);
    printf("Bob sends to Alice: %llu\n", B);
    unsigned long long secret_Alice = modExp(B, x_Alice, q);
    printf("Alice computes shared secret: %llu\n", secret_Alice);
    unsigned long long secret_Bob = modExp(A, x_Bob, q);
    printf("Bob computes shared secret: %llu\n", secret_Bob);

    if (secret_Alice == secret_Bob) {
        printf("Shared secret established successfully!\n");
    } else {
        printf("Error: Shared secrets do not match.\n");
    }

    return 0;
}

