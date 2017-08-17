#include <iostream>
#include <vector>
#include <cmath>

typedef long long int64;

int main()
{
    long long target_sum, size;

    std::cin >> target_sum >> size;

    int max_gcd = -1;

    int64 current_sum = 0;
    int current_gcd = 1;

    /**
     * As the progression must be strictly increasing and all elements must be divisible by `current_gcd`, to achieve a
     * gcd of `current_gcd`, we need at least the following arithmetic progression: `current_gcd` .. n * `current_gcd`
     */

    while(current_sum < target_sum) {
        current_sum = current_gcd * size * (size + 1) / 2;

        /**
         * The current such progression has the target sum or we can achieve the target sum by distributing excess
         * part of the target sum in chunks of size `current_gcd` across the elements
         */

        if(current_sum <= target_sum && target_sum % current_gcd == 0) {
            max_gcd = current_gcd;
        }

        current_gcd += 1;
    }

    std::cout << max_gcd << std::endl;
}
