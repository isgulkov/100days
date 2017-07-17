#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdint.h>

/**
 * @param s String of specified size
 * @param size Size of the provided string
 * @param result Pointer to an array of the specified size for the values of the prefix function to be stored
 */
void compute_prefix_function(char* s, size_t size, size_t* result)
{
    result[0] = 0;

    for(int i = 1; i <= size; i++) {
        size_t j = result[i - 1];

        while(j > 0 && s[i] != s[j]) {
            j = result[j - 1];
        }

        if(s[i] == s[j]) {
            j += 1;
        }

        result[i] = j;
    }
}

/**
 * @param length Length of the provided string
 * @param p_last Last value of the provided string's prefix function
 * @return Length of the shortest period of string s
 */
size_t min_period(size_t length, size_t p_last)
{
    if(length % (length - p_last) == 0) {
        return length - p_last;
    }
    else {
        return length;
    }
}

int main()
{
    char s[8001];

    scanf("%s", s);

    size_t s_length = strlen(s);

    /**
     * Precompute the values of the prefix function for all suffixes of `s` so that prefix_function[i][j] stores the
     * last value of prefix function of substring [i; j)
     */
    size_t* prefix_function[8000];

    for(int i = 0; i < 8000; i++) {
        prefix_function[i] = malloc(sizeof(size_t) * 8000);
    }

    for(int i = 0; i < s_length; i++) {
        compute_prefix_function(s + i, s_length - i, prefix_function[i] + i);
    }

    /**
     * Precompute "floor(logarithm base 10) + 1" values as the math.h log10 floating point function is hella slow
     */
    size_t log10plus1_values[8001];

    log10plus1_values[0] = 0;

    for(int i = 1; i <= 8000; i++) {
        log10plus1_values[i] = log10plus1_values[i / 10] + 1;
    }

    /**
     * dp[i] stores the minimum number of chars required for encoding the [0; i) substring
     */

    size_t* dp = malloc(sizeof(size_t) * s_length);
    dp[0] = 0;

    for(size_t i = 1; i <= s_length; i++) {
        dp[i] = SIZE_MAX;

        for(size_t j = 0; j < i; j++) {
            /**
             * Try to write substring [j; i) as its minimum period with the number of repetitions prepended
             */

            size_t substr_min_period = min_period(i - j, prefix_function[j][i - 1]);

            size_t candidate_answer = dp[j];

            /**
             * Length of the minimum period string
             */
            candidate_answer += substr_min_period;

            /**
             * Number of decimal digits needed to write down the number of repetitions
             */
            candidate_answer += log10plus1_values[(i - j) / substr_min_period];

            if(candidate_answer < dp[i]) {
                dp[i] = candidate_answer;
            }
        }
    }

    printf("%ld\n", dp[s_length]);
}
