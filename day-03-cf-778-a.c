#include <stdio.h>
#include <string.h>

/*
 * Returns whether string `p` is a subsequence of string `t` with characters skipped at positions for which
 * corresponding booleans in `t_removed_positions` are set
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

    int t_removed_positions[200001];

    for(int i = 0; i < t_length; i++) {
        t_removed_positions[i] = 0;
    }

    for(int i = 0; i < t_length; i++) {
        int pos;

        scanf("%d", &pos);

        t_removed_positions[pos - 1] = 1;

        if(!is_a_subsequence(p, t, t_removed_positions)) {
            printf("%d", i);
            break;
        }
    }

    for(int i = 0; i < t_length; i++) {
        int pos;

        scanf("%d", &pos);
    }

    return 0;
}
