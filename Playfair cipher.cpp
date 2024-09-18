#include <stdio.h>
#include <math.h>

unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    int characters = 25;
    unsigned long long total_keys = factorial(characters);
    double approx_keys_in_power_of_2 = log2(total_keys);
    unsigned long long symmetric_permutations = 2;  
    unsigned long long unique_keys = total_keys / symmetric_permutations;
    double approx_unique_keys_in_power_of_2 = log2(unique_keys);
    printf("Total possible keys: %llu\n", total_keys);
    printf("Approximate total keys in power of 2: %.2f\n", approx_keys_in_power_of_2);
    printf("Unique keys (considering symmetry): %llu\n", unique_keys);
    printf("Approximate unique keys in power of 2: %.2f\n", approx_unique_keys_in_power_of_2);

    return 0;
}

