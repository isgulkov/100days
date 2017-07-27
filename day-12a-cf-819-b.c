#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/**
 * Represents a `long long` array of size `length` with following operations defined:
 * * add arithmetic progression to a range of elements in constant time;
 * * get minimum value in linear time
 *
 * Values of elements, as well as the array minimum, can only be obtained in O(n) time and don't get updated with each
 * modification request, hence the name "offline"
 */
struct offline_segment
{
    int length;
    long long* values;
    long long* deltas;
};

void build_segment(struct offline_segment* segment, int length)
{
    segment->length = length;

    segment->values = malloc(sizeof(long long) * length);
    segment->deltas = malloc(sizeof(long long) * length);

    for(int i = 0; i < length; i++) {
        segment->values[i] = 0;
        segment->deltas[i] = 0;
    }
}

void add_progression(struct offline_segment* segment, int l, int r, int first, int diff)
{
    if(l < segment->length) {
        segment->values[l] += first;
        segment->deltas[l] += diff;
    }

    if(r < segment->length) {
        segment->values[r] -= first;
        segment->values[r] -= diff * (r - l);
        segment->deltas[r] -= diff;
    }
}

/**
 * Add values of arithmetic progression starting with `first` with difference -1 from elements with indices [l; r)
 *
 * Time complexity: O(1)
 */
void add_decreasing(struct offline_segment* segment, int l, int r, int first)
{
    add_progression(segment, l, r, first, -1);
}

/**
 * Subtract values of arithmetic progression starting with `first` with difference -1 from elements with indices [l; r)
 *
 * Time complexity: O(1)
 */
void subtract_decreasing(struct offline_segment* segment, int l, int r, int first)
{
    add_progression(segment, l, r, -first, 1);
}

/**
 * Get minimum value in the segment as well as its index
 *
 * Time complexity: O(n)
 * Space complexity: O(n) (can be redone in O(1) even without destroying the data structure)
 */
long long get_minimum(struct offline_segment* segment, int* min_index_ptr)
{
    /**
     * Interpolate deltas
     */
    long long* deltas_inpterp = malloc(sizeof(long long) * segment->length);

    deltas_inpterp[0] = segment->deltas[0];

    for(int i = 1; i < segment->length; i++) {
        deltas_inpterp[i] = segment->deltas[i] + deltas_inpterp[i - 1];
    }

    /**
     * Apply deltas to partial values
     */
    long long* restored_values = malloc(sizeof(long long) * segment->length);

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

    long long min_value = LONG_LONG_MAX;
    int min_index = -1;

    for(int i = 0; i < segment->length; i++) {
        if(restored_values[i] < min_value) {
            min_value = restored_values[i];
            min_index = i;
        }
    }

    free(deltas_inpterp);
    free(restored_values);

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
        /**
         * Add to deviation of each shift the share of this permutation element:
         *
         * abs(perm[i] - ((i + shift) % n + 1))
         *
         * with abs and modulo opened up, so that these can be added to ranges of deviations at once (as arithmetic
         * progressions), which can be performed in O(1) time
         */

        if(perm[i] >= i + 1) {
            add_decreasing(&deviations, 0, perm[i] - i, perm[i] - (i + 1));

            subtract_decreasing(&deviations, perm[i] - i, n - i, -1);

            add_decreasing(&deviations, n - i, n, perm[i] - 1);
        }
        else {
            subtract_decreasing(&deviations, 0, n - i, perm[i] - (i + 1));

            add_decreasing(&deviations, n - i, n - i + perm[i], perm[i] - 1);

            subtract_decreasing(&deviations, n - i + perm[i], n, -1);
        }
    }

    int min_shift;
    long long min_deviation = get_minimum(&deviations, &min_shift);

    printf("%lld %d\n", min_deviation, min_shift);

    return 0;
}
