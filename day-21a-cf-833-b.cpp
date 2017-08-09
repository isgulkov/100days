#include <iostream>
#include <vector>
#include <unordered_map>

class max_segtree
{
    struct segtree_node
    {
        int maxval, change;

        int l, r;

        segtree_node* left;
        segtree_node* right;

        segtree_node(int l, int r, const std::vector<int>& values) : change(0), l(l), r(r)
        {
            if(l == r) {
                maxval = values[l];

                left = nullptr;
                right = nullptr;
            }
            else {
                int mid = (l + r) / 2;

                left = new segtree_node(l, mid, values);
                right = new segtree_node(mid + 1, r, values);

                maxval = std::max(left->maxval, right->maxval);
            }
        }

        int get_max(int start, int end)
        {
            if(change != 0) {
                push_change();
            }

            if(start == l && end == r) {
                return maxval;
            }
            else {
                int mid = (l + r) / 2;

                if(end <= mid) {
                    return left->get_max(start, end);
                }
                else if(start > mid) {
                    return right->get_max(start, end);
                }
                else {
                    return std::max(
                            left->get_max(start, mid),
                            right->get_max(mid + 1, end)
                    );
                }
            }
        }

        void push_change()
        {
            if(left != nullptr /* && right != nullptr */) {
                left->change += change;
                right->change += change;
            }

            maxval += change;
            change = 0;
        }

        void increment_range(int start, int end)
        {
            if(change != 0) {
                push_change();
            }

            if(start == l && end == r) {
                change += 1;
            }
            else {
                int mid = (l + r) / 2;

                if(end <= mid) {
                    left->increment_range(start, end);
                }
                else if(start > mid) {
                    right->increment_range(start, end);
                }
                else {
                    left->increment_range(start, mid);
                    right->increment_range(mid + 1, end);
                }

                maxval = std::max(left->get_max(l, mid), right->get_max(mid + 1, r));
            }
        }
    };

    segtree_node* root;

public:
    max_segtree(const std::vector<int>& init)
    {
        root = new segtree_node(0, (int)init.size() - 1, init);
    }

    int get_max(int start, int end)
    {
        return root->get_max(start, end);
    }

    void increment_range(int start, int end)
    {
        root->increment_range(start, end);
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
            if(i_cake != 0) {
                max_score[i_cake] = t.get_max(0, i_cake - 1);
            }

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
