#include <stdio.h>
#include <string.h>

/*
 * Returns whether string `p` is a subsequence of string `t` with characters skipped at positions for which
 * corresponding booleans in `t_removed_positions` are set
 *
 * Time complexity: O(|p| + |t|)
 */
int is_a_subsequence(char* p, char* t, int* t_removed_positions)
{
    int pos_p = 0, pos_t = 0;

    while(p[pos_p] != '\0' && t[pos_t] != '\0') {
        if(!t_removed_positions[pos_t] && p[pos_p] == t[pos_t]) {
            pos_p += 1;
        }

        pos_t += 1;
    }

    return p[pos_p] == '\0';
}

int main()
{
    char t[200001], p[200001];

    scanf("%s\n", t);
    scanf("%s\n", p);

    size_t t_length = strlen(t);
    size_t p_length = strlen(p);

    int removals[200001];

    for(int i = 0; i < t_length; i++) {
        int removal;

        scanf("%d", &removal);

        removals[i] = removal - 1;
    }

    /*
     * Inclusive boundaries of binary search
     */
    size_t left = 0, right = t_length;

    size_t old_mid = 0;

    int t_removed_positions[200001];

    for(int i = 0; i < t_length; i++) {
        t_removed_positions[i] = 0;
    }

    while(left != right) {
        size_t mid = left + (right - left) / 2;

        while(old_mid < mid) {
            t_removed_positions[removals[old_mid++]] = 1;
        }

        while(old_mid > mid) {
            t_removed_positions[removals[--old_mid]] = 0;
        }

        /*
         * At this point removals at [0; mid) are applied, removals at [mid; t_length) are not applied
         */

        if(is_a_subsequence(p, t, t_removed_positions)) {
            left = mid + 1;
        }
        else {
            right = mid;
        }
    }

    printf("%zu\n", left - 1);

    return 0;
}
