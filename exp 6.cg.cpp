#include <stdio.h>
#include <ctype.h>
#define ALPHABET_SIZE 26
int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; 
}
char affine_decrypt(char c, int a, int b, int m) {
    if (!isalpha(c)) return c; 
    int x = toupper(c) - 'A'; 
    int a_inv = mod_inverse(a, m);
    if (a_inv == -1) {
        printf("No modular inverse found for a = %d\n", a);
        return c;
    }
    int decrypted = (a_inv * (x - b + m)) % m;
    return decrypted + 'A';
}

int main() {
    char ciphertext[] = "VWLCR..."; 
    char most_frequent_letter = 'B'; 
    char second_most_frequent_letter = 'U'; 
    char expected_most_frequent = 'E'; 
    char expected_second_most_frequent = 'T'; 
    int a, b; 
    int m = ALPHABET_SIZE;
    for (a = 1; a < m; a++) {
        if (mod_inverse(a, m) == -1) continue;

        for (b = 0; b < m; b++) {
            char decrypted_most_frequent = affine_decrypt(most_frequent_letter, a, b, m);
            char decrypted_second_frequent = affine_decrypt(second_most_frequent_letter, a, b, m);

            if (decrypted_most_frequent == expected_most_frequent &&
                decrypted_second_frequent == expected_second_most_frequent) {
                printf("Possible keys found: a = %d, b = %d\n", a, b);
                printf("Decryption with a = %d, b = %d:\n", a, b);
                for (int i = 0; ciphertext[i] != '\0'; i++) {
                    printf("%c", affine_decrypt(ciphertext[i], a, b, m));
                }
                printf("\n");
                return 0;
            }
        }
    }
    
    printf("No valid keys found\n");
    return 1;
}

