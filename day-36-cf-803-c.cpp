#include <iostream>
#include <vector>
#include <cmath>

typedef long long int64;

int main()
{
    long long target_sum, size;

    std::cin >> target_sum >> size;

    /**
     * As the progression must be strictly increasing and all elements must be divisible by `current_gcd`, to achieve a
     * gcd of `current_gcd`, we need at least the following arithmetic progression: g .. n * g, where g is its GCD
     */

    int64 max_gcd = -1;

    for(int64 i = 1; i * i <= target_sum; i++) {
        if(target_sum % i != 0) {
            continue;
        }

        /**
         * Iterate over all divisors of `target_sum` -- for every divisor less than the square root of the number, there
         * is exactly one greater than that
         */
        for(int64 current_gcd : { i, target_sum / i}) {
            /**
             * Calculate the sum of progression in 80-bit float to avoid overflow
             */
            long double current_sum = (long double)current_gcd * size * (size + 1) / 2;

            if(current_gcd > max_gcd && current_sum <= target_sum) {
                max_gcd = current_gcd;
            }
        }
    }

    if(max_gcd == -1) {
        std::cout << max_gcd << std::endl;
    }
    else {
        for(int i = 1; i < size; i++) {
            std::cout << max_gcd * i << " ";

            target_sum -= max_gcd * i;
        }

        /**
         * Dump anything that's left into the last element
         */
        std::cout << target_sum << std::endl;
    }
}
