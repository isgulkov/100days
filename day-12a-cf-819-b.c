#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;

    scanf("%d", &n);

    int* perm = malloc(sizeof(int) * n);

    for(int i = 0; i < n; i++) {
        scanf("%d", perm + i);
    }

    for(int i = 0; i < n; i++) {
        printf("%d ", perm[i]);
    }

    return 0;
}
