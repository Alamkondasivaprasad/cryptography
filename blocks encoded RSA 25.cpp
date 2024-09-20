#include <stdio.h>
unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    unsigned long long n, plaintext_block, e;
    n = 3233; 
    e = 17;   
    plaintext_block = 1769; 
    unsigned long long factor = gcd(plaintext_block, n);

    if (factor > 1 && factor < n) {
        printf("Found a non-trivial common factor with n: %llu\n", factor);
        unsigned long long other_factor = n / factor;
        printf("The other prime factor is: %llu\n", other_factor);
    } else {
        printf("No common prime factor found.\n");
    }

    return 0;
}

