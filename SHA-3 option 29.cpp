#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUM_LANES 25  
#define RATE_BITS 1024
#define LANE_SIZE_BITS 64  
void initialize_state(unsigned long long state[NUM_LANES], int capacity_lanes) {
    for (int i = 0; i < NUM_LANES; i++) {
        if (i >= capacity_lanes) {
            state[i] = rand() % 0xFFFFFFFFFFFFFFFFULL; 
        } else {
            state[i] = 0; 
        }
    }
}
void process_message_block(unsigned long long state[NUM_LANES]) {
    for (int i = 0; i < NUM_LANES; i++) {
        if (state[i] == 0) {
            state[i] = rand() % 0xFFFFFFFFFFFFFFFFULL; 
        }
    }
}
int all_lanes_nonzero(unsigned long long state[NUM_LANES], int capacity_lanes) {
    for (int i = 0; i < capacity_lanes; i++) {
        if (state[i] == 0) {
            return 0; 
        }
    }
    return 1; 
}

int main() {
    srand(time(0)); 
    int capacity_lanes = (1600 - RATE_BITS) / LANE_SIZE_BITS; 
    
    unsigned long long state[NUM_LANES]; 
    initialize_state(state, capacity_lanes);
    printf("Initial state (Capacity lanes):\n");
    for (int i = 0; i < capacity_lanes; i++) {
        printf("Lane %d: %llu\n", i, state[i]);
    }

    int rounds = 0;
    while (!all_lanes_nonzero(state, capacity_lanes)) {
        process_message_block(state); 
        rounds++;
    }
    printf("\nAll lanes non-zero after %d rounds\n", rounds);
    printf("\nFinal state (Capacity lanes):\n");
    for (int i = 0; i < capacity_lanes; i++) {
        printf("Lane %d: %llu\n", i, state[i]);
    }

    return 0;
}

