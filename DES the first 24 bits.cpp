#include <stdio.h>
#include <stdint.h>

uint64_t Left_Shift(uint64_t val, int shifts) { return ((val << shifts) & 0x0FFFFFFF) | (val >> (28 - shifts)); }

void Key_Schedule(uint64_t key, uint64_t subkeys[16]) {
    uint64_t C = (key >> 36) & 0x0FFFFFFF; 
    uint64_t D = (key >> 8) & 0x0FFFFFFF;  

    for (int i = 0; i < 16; i++) {
        C = Left_Shift(C, 1);              
        D = Left_Shift(D, 1);              
        subkeys[i] = ((C & 0xFFFFFF) << 24) | (D & 0xFFFFFF); 
    }
}

int main() {
    uint64_t key = 0x133457799BBCDFF1, subkeys[16];
    Key_Schedule(key, subkeys);            

    for (int i = 0; i < 16; i++)
        printf("Subkey %d: %lx\n", i + 1, subkeys[i]);
    
    return 0;
}

