#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct substring_occurence
{
    int start_index;
    char* substring;
} substring_occurence;

int compare_substring_occurences(const void* one, const void* another)
{
    return ((substring_occurence*)one)->start_index - ((substring_occurence*)another)->start_index;
}

int main()
{
    int n;

    scanf("%d", &n);

    /*
     * A 5MB array can't be expected to be successfully allocated on the stack, so allocate it in heap
     */
    substring_occurence* occurences = malloc(sizeof(substring_occurence) * 1000000);
    size_t num_occurences = 0;

    for(int i = 0; i < n; i++) {
        char buf[1000001];
        int k;

        scanf("%s %d", buf, &k);

        char* substring = malloc(sizeof(char) * strlen(buf));
        strcpy(substring, buf);

        for(int j = 0; j < k; j++) {
            int start_index;

            scanf("%d", &start_index);

            occurences[num_occurences].start_index = start_index - 1; // Make indices zero-based
            occurences[num_occurences].substring = substring;

            num_occurences += 1;
        }
    }

    qsort(occurences, num_occurences, sizeof(substring_occurence), &compare_substring_occurences);

    for(int i = 0; i < num_occurences; i++) {
        printf("%d %s\n", occurences[i].start_index, occurences[i].substring);
    }

    return 0;
}
