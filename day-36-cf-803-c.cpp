#include <iostream>
#include <vector>
#include <cmath>

typedef long long int64;

int main()
{
    long long target_sum, size;

    std::cin >> target_sum >> size;

    int64 max_gcd = -1;

    /**
     * As the progression must be strictly increasing and all elements must be divisible by `current_gcd`, to achieve a
     * gcd of `current_gcd`, we need at least the following arithmetic progression: g .. n * g, where g is its GCD
     */

    if(size > 1000 * 1000) {
        /**
         * With big enough `size` expressions in the following code may oveflow over the 64-bit integer, but maximum
         * `size` for which a sequence is achievable with `target_sum` at the maximum 10^10 is about 141 000 anyway
         */

        std::cout << -1 << std::endl;

        return 0;
    }

    /**
     * The target sum must be divisible by the GCD, so iterate over all divisors
     */

    for(int64 i = 1; i * i <= target_sum; i++) {
        if(target_sum % i != 0) {
            continue;
        }

        /**
         * For every divisor less than the square root of the number, there is exactly one greater than it
         */
        for(int64 current_gcd : { i, target_sum / i}) {
            int64 current_sum = current_gcd * size * (size + 1) / 2;

            if(current_gcd > max_gcd && current_sum <= target_sum) {
                max_gcd = current_gcd;
            }

            current_gcd += 1;
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
