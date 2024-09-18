#include <stdio.h>
#include <stdint.h>

uint64_t XOR(uint64_t a, uint64_t b) { return a ^ b; }
uint64_t Initial_Permutation(uint64_t input) { return input; }
uint64_t Inverse_Initial_Permutation(uint64_t input) { return input; }
uint64_t Expansion(uint32_t half) { return (uint64_t)half; }
uint32_t SBox_Substitution(uint64_t input) { return (uint32_t)input; }
uint32_t Permutation_P(uint32_t input) { return input; }
void Key_Schedule(uint64_t key, uint64_t round_keys[16]) { for (int i = 0; i < 16; i++) round_keys[i] = key; }

uint64_t DES_Decryption(uint64_t ciphertext, uint64_t key) {
    uint64_t permuted_text = Initial_Permutation(ciphertext), round_keys[16], R = permuted_text & 0xFFFFFFFF, L = permuted_text >> 32;
    Key_Schedule(key, round_keys);
    for (int i = 0; i < 16; i++) { uint64_t expanded_R = Expansion(R); uint32_t substituted = SBox_Substitution(XOR(expanded_R, round_keys[15 - i])); uint32_t new_R = L ^ Permutation_P(substituted); L = R; R = new_R; }
    return Inverse_Initial_Permutation(((uint64_t)R << 32) | L);
}

int main() {
    uint64_t ciphertext = 0x0123456789ABCDEF, key = 0x133457799BBCDFF1;
    printf("Decrypted text: %lx\n", DES_Decryption(ciphertext, key));
}

