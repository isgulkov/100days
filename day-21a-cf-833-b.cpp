#include <iostream>
#include <vector>
#include <unordered_map>

class max_segtree // stub for segment tree
{
    std::vector<int> xs;

public:
    max_segtree(const std::vector<int>& init) : xs(init.size())
    {
        // Replace with copy-constructor

        for(int i = 0; i < init.size(); i++) {
            xs[i] = init[i];
        }
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

    std::vector<int> max_score((size_t)num_cakes + 1, INT32_MIN);

    max_score[0] = 0;

    for(int i_box = 0; i_box < num_boxes; i_box++) {
        max_segtree t(max_score);

        for(int i_cake = 0; i_cake <= num_cakes; i_cake++) {
            max_score[i_cake] = t.get_max(0, i_cake - 1);

            if(i_cake != num_cakes) {
                t.increment_range(prev_occurrence[i_cake] + 1, i_cake);
            }
        }
    }

    std::cout << max_score[num_cakes] << std::endl;
}
