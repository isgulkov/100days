#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

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

    free(prefix_function);

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

    for(size_t i = 1; i <= s_length; i++) {
        printf("%c %ld %ld %ld\n", s[i - 1], i, prefix_function_last(s, i), min_period(s, i));
    }

}
