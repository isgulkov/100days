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

    size_t prefix_last = prefix_function[size];

    free(prefix_function);

    return prefix_last;
}

int main()
{
    char s[8001];

    scanf("%s", s);

    size_t s_length = strlen(s);

    for(int i = 1; i < s_length; i++) {
        printf("%ld ", prefix_function_last(s, i));
    }

}
