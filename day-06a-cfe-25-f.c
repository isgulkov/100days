#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <stdint.h>

/**
 * @param s String of specified size
 * @param size Size of the provided string
 * @return Last value of the prefix function of the provided string
 */
size_t prefix_function_last(char* s, size_t size)
{
    size_t* prefix_function = malloc(sizeof(size_t) * size);
    prefix_function[0] = 0;

    for(int i = 1; i <= size; i++) {
        size_t j = prefix_function[i - 1];

        while(j > 0 && s[i] != s[j]) {
            j = prefix_function[j - 1];
        }

        if(s[i] == s[j]) {
            j += 1;
        }

        prefix_function[i] = j;
    }

    size_t prefix_last = prefix_function[size - 1];

//    free(prefix_function);

    return prefix_last;
}

/**
 * @param s String of specified size
 * @param size Size of the provided string
 * @return Length of the shortest period of string s
 */
size_t min_period(char* s, size_t size)
{
    size_t p_last = prefix_function_last(s, size);

    if(size % (size - p_last) == 0) {
        return size - p_last;
    }
    else {
        return size;
    }
}

int main()
{
    char s[8001];

    scanf("%s", s);

    size_t s_length = strlen(s);

    size_t* dp = malloc(sizeof(size_t) * s_length);
    dp[0] = 0;

    /**
     * dp[i] stores the minimum number of chars required for encoding the [0; i) substring
     */
    for(size_t i = 1; i <= s_length; i++) {
        dp[i] = SIZE_MAX;

        for(size_t j = 0; j < i; j++) {
            /**
             * Try to write substring [j; i) as its minimum period with the number of repetitions prepended
             */

            size_t substr_min_period = min_period(s + j, i - j);

            size_t candidate_answer = dp[j];

            /**
             * Length of the minimum period string
             */
            candidate_answer += substr_min_period;

            /**
             * Number of decimal digits needed to write down the number of repetitions
             */
            candidate_answer += (int)log10((i - j) / substr_min_period) + 1;

            if(candidate_answer < dp[i]) {
                dp[i] = candidate_answer;
            }
        }
    }

    printf("%ld\n", dp[s_length]);
}
