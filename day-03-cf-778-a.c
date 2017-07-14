#include <stdio.h>
#include <string.h>

int main()
{
    char t[200001], p[200001];

    scanf("%s\n", t);
    scanf("%s\n", p);

    size_t t_length = strlen(t);
    size_t p_length = strlen(p);

    int is[200000];

    for(int i = 0; i < t_length; i++) {
        scanf("%d", &is[i]);
    }

    return 0;
}
