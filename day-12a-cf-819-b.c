#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct offline_segment
{
    int length;
    int* values;
    int* deltas;
};

void build_segment(struct offline_segment* segment, int length)
{
    segment->length = length;

    segment->values = malloc(sizeof(int) * length);
    segment->deltas = malloc(sizeof(int) * length);

    for(int i = 0; i < length; i++) {
        segment->values[i] = 0;
        segment->deltas[i] = 0;
    }
}

/**
 * Add values of arithmetic progression starting with `first` with difference -1 from elements with indices [l; r)
 *
 * Time complexity: O(1)
 */
void add_decreasing(struct offline_segment* segment, int l, int r, int first)
{
    if(l < segment->length) {
        segment->values[l] += first;
        segment->deltas[l] += -1;
    }

    if(r < segment->length) {
        segment->values[r] -= -(r - l) + first;
        segment->deltas[r] -= -1;
    }
}

/**
 * Subtract values of arithmetic progression starting with `first` with difference 1 from elements with indices [l; r)
 *
 * Time complexity: O(1)
 */
void subtract_increasing(struct offline_segment* segment, int l, int r, int first)
{
    if(l < segment->length) {
        segment->values[l] += -first;
        segment->deltas[l] += 1;
    }

    if(r < segment->length) {
        segment->values[r] -= r - l - first;
        segment->deltas[r] -= 1;
    }
}

/**
 * Get minimum values in the segment as well as its index
 *
 * Time complexity: O(n)
 * Space complexity: O(n) (can be redone in O(1) even without destroying the data structure)
 */
int get_minimum(struct offline_segment* segment, int* min_index_ptr)
{
    /**
     * Interpolate deltas
     */
    int* deltas_inpterp = malloc(sizeof(int) * segment->length);

    deltas_inpterp[0] = segment->deltas[0];

    for(int i = 1; i < segment->length; i++) {
        deltas_inpterp[i] = segment->deltas[i] + deltas_inpterp[i - 1];
    }

    /**
     * Apply deltas to partial values
     */
    int* restored_values = malloc(sizeof(int) * segment->length);

    restored_values[0] = segment->values[0];

    for(int i = 1; i < segment->length; i++) {
        restored_values[i] = segment->values[i] + deltas_inpterp[i - 1];
    }

    /**
     * Restore values
     */
    for(int i = 1; i < segment->length; i++) {
        restored_values[i] += restored_values[i - 1];
    }

    int min_value = INT_MAX;
    int min_index = -1;

    for(int i = 0; i < segment->length; i++) {
        if(restored_values[i] < min_value) {
            min_value = restored_values[i];
            min_index = i;
        }
    }

    if(min_index_ptr != NULL) {
        *min_index_ptr = min_index;
    }

    return min_value;
}

int main()
{
    int n;

    scanf("%d", &n);

    int* perm = malloc(sizeof(int) * n);

    for(int i = 0; i < n; i++) {
        scanf("%d", perm + i);
    }

    struct offline_segment deviations;

    build_segment(&deviations, n);

    for(int i = 0; i < n; i++) {
        if(perm[i] >= i + 1) {
            add_decreasing(&deviations, 0, perm[i] - i, perm[i] - (i + 1));

            subtract_increasing(&deviations, perm[i] - i, n - i, perm[i] - (i + perm[i] - i + 1));

            add_decreasing(&deviations, n - i, n, perm[i] - (i + n - i - n + 1));
        }
        else {
            subtract_increasing(&deviations, 0, n - i, perm[i] - (i + 1));

            add_decreasing(&deviations, n - i, n - i + perm[i], perm[i] - (i + n - i - n + 1));

            subtract_increasing(&deviations, n - i + perm[i], n, perm[i] - (i + n - i + perm[i] - n + 1));
        }
    }

    int min_deviation, min_shift;

    min_deviation = get_minimum(&deviations, &min_shift);

    printf("%d %d\n", min_deviation, min_shift);

    return 0;
}
