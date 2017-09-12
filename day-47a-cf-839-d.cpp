#include <iostream>
#include <vector>
#include <algorithm>

int power_mod_p(int a, int k, int p)
{
    int64_t result = 1LL;

    int64_t current_binary_power = a;

    while(k) {
        if(k & 1) {
            result *= current_binary_power;
            result %= p;
        }

        current_binary_power *= current_binary_power;
        current_binary_power %= p;

        k >>= 1;
    }

    return (int)(result % p);
}

int main()
{
    int num_soldiers;

    std::cin >> num_soldiers;

    std::vector<int> strengths((size_t)num_soldiers);

    for(int i = 0; i < num_soldiers; i++) {
        std::cin >> strengths[i];
    }

    /**
     * For each `i` in [2; MAX_STRENGTH] calculate how many strengths are divisible by `i`
     */

    const int MAX_STRENGTH = *std::max_element(strengths.begin(), strengths.end());

    std::vector<int> num_multiples_of((size_t)(MAX_STRENGTH + 1), 0);

    for(int i = 0; i < num_soldiers; i++) {
        num_multiples_of[strengths[i]] += 1;
    }

    for(int i = 2; i <= MAX_STRENGTH; i++) {
        for(int k = 2; i * k <= MAX_STRENGTH; k++) {
            /**
             * Numbers divisible by k * i are also divisible by i.
             *
             * Thus, for any number `j`, all its divisors `i` will contribute to the `j`'s result
             */

            num_multiples_of[i] += num_multiples_of[i * k];
        }
    }

    /**
     * For every potential GCD, calculate the sum of sizes for subsets with that GCD (modulo P)
     */

    const int P = 1000 * 1000 * 1000 + 7;

    std::vector<int> total_size_with_gcd((size_t)(MAX_STRENGTH + 1), 0);

    for(int i = MAX_STRENGTH; i >= 1; i--) {
        if(num_multiples_of[i] == 0) {
            continue;
        }

        /**
         * Sum of sizes for subsets where all strengths are divisible by `i`:
         *   1 * C(n, 1) + 2 * C(n, 2) + ... + n * C(n, n),
         * where n = num_multiples_of[`i`], C(n, k) is the number of subsets of size k, so the sum of sizes of such
         * subsets is k * C(n, k). After simplification the above expression becomes
         *   n * (C(n - 1, 0) + ... + C(n - 1, n - 1)) = n * 2^(n - 1)
         */
        int64_t total_elements = 1LL * num_multiples_of[i] * power_mod_p(2, num_multiples_of[i] - 1, P);

        for(int k = 2; i * k <= MAX_STRENGTH; k++) {
            /**
             * Subtract the figures for all `k` * `i`, as such subsets will have the higher GCD `k` * `i` instead of `i`
             */

            total_elements -= total_size_with_gcd[i * k];
            total_elements %= P;
        }

        total_size_with_gcd[i] = (int)(total_elements % P);
    }

    int64_t result = 0;

    for(int i = 2; i <= MAX_STRENGTH; i++) {
        result += 1LL * i * total_size_with_gcd[i];
        result %= P;
    }

    std::cout << (result + P) % P << std::endl;
}
