#include <iostream>
#include <vector>
#include <unordered_map>

class max_segtree // stub for segment tree
{
    std::vector<int> xs;

public:
    max_segtree(const std::vector<int>& init) : xs(init)
    {

    }

    int get_max(int start, int end)
    {
        int result = INT32_MIN;

        for(int i = start; i <= end; i++) {
            if(xs[i] > result) {
                result = xs[i];
            }
        }

        return result;
    }

    void increment_range(int start, int end)
    {
        for(int i = start; i <= end; i++) {
            xs[i] += 1;
        }
    }
};

int main()
{
    int num_cakes, num_boxes;

    std::cin >> num_cakes >> num_boxes;

    std::vector<int> cakes((size_t)num_cakes);

    for(int i = 0; i < num_cakes; i++) {
        std::cin >> cakes[i];
    }

    /**
     * Each prev_occurrence[i] stores the index of the last element in `cakes` that is equal to cakes[i] and goes
     * strictly before it. -1 if there are no such elements
     */
    std::vector<int> prev_occurrence((size_t)num_cakes, -1);

    {
        std::unordered_map<int, int> last_occurrence;

        for(int i = 0; i < num_cakes; i++) {
            if(last_occurrence.find(cakes[i]) != last_occurrence.end()) {
                prev_occurrence[i] = last_occurrence[cakes[i]];
            }

            last_occurrence[cakes[i]] = i;
        }
    }

    /**
     * Each max_score[i] stores maximum score achievable by putting the first `i` cakes into the current number of boxes
     */
    std::vector<int> max_score((size_t)num_cakes + 1, 0);

    for(int i_box = 1; i_box <= num_boxes; i_box++) {
        /**
         * Before `i_cake`th step elements [0; i_cake] of the segment tree will hold
         *   T[0] = 0
         *   T[i] = dp(i_box - 1, i) + score(i, i_cake - 1),
         * where dp(x, y) is the maximum score achievable by packing first `y` cakes into `x` boxes, and score(x, y) is
         * the score of a box encompassing cakes [x; y].
         *
         * Therefore dp(i_box, i_cake) will be equal to the maximum of elements [0; i_cake] of this segment tree.
         */
        max_segtree t(max_score);

        for(int i_cake = 0; i_cake <= num_cakes; i_cake++) {
            max_score[i_cake] = t.get_max(0, i_cake - 1);

            if(i_cake != num_cakes) {
                /**
                 * The addition of (i_cake - 1)th cake to the last box will only increment only the T(i)s where the last
                 * box doesn't have cakes of type cakes[i_cake - 1].
                 */
                t.increment_range(prev_occurrence[i_cake] + 1, i_cake);
            }
        }
    }

    std::cout << max_score[num_cakes] << std::endl;
}
