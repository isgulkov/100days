#include <iostream>
#include <vector>

/**
 * Returns whether `x` is a square of an integer
 *
 * Time complexity: log(x)
 */
bool is_square(int64_t x)
{
    int64_t l = 0;
    int64_t r = x;

    while(l < r) {
        int64_t mid = l + (r - l) / 2;

        if(mid * mid > x) {
            r = mid - 1;
        }
        else if(mid * mid < x) {
            l = mid + 1;
        }
        else {
            return true;
        }
    }

    return l * l == x;
}

class binomial_calculator
{
    std::vector<std::vector<int64_t>> pascal_rows;

    int num_rows = 0;

public:
    binomial_calculator()
    {
        pascal_rows.push_back({ 1 });

        num_rows = 1;
    }

    /**
     * Returns binomial coefficient C(n, k)
     *
     * Time complexity: O(1) (amortized for max(n) * max(k) requests, where max(n) is the largest `n` among a sequence
     *                        of requests)
     *                  O(n) (amortized for max(n) requests)
     */
    int64_t get_binomial(int64_t n, int64_t k)
    {
        if(k > n) {
            throw -1;
        }

        while(num_rows <= n) {
            /**
             * Calculate the next row of the Pascal triangle
             */

            pascal_rows.push_back(std::vector<int64_t>((size_t)num_rows + 1));

            std::vector<int64_t>& prev_row = pascal_rows[num_rows - 1];
            std::vector<int64_t>& last_row = pascal_rows[num_rows];

            last_row[0] = 1;

            for(int i = 1; i < last_row.size() - 1; i++) {
                last_row[i] = prev_row[i - 1] + prev_row[i];
            }

            last_row[last_row.size() - 1] = 1;

            num_rows += 1;
        }

        return pascal_rows[n][k];
    }
};

class factorial_mod_p_calculator
{
    std::vector<int64_t> facts {1};

    int64_t p;

public:
    factorial_mod_p_calculator(int64_t p) : p(p) { }

    /**
     * Returns the factorial of `n` modulo `p`
     *
     * Time complexity: O(1) (amortized for max(n) requests)
     */
    int64_t get_factorial(int64_t n)
    {
        while(facts.size() <= n) {
            facts.push_back((int64_t)facts.size() * facts.back() % p);
        }

        return facts[n];
    }
};

int main()
{
    int num_items;

    std::cin >> num_items;

    std::vector<int> xs((size_t)num_items);

    for(int i = 0; i < num_items; i++) {
        std::cin >> xs[i];
    }

    /**
     * Divide the numbers into groups s.t. product of any two numbers from the same group is a square of integer
     */

    std::vector<int> x_groups((size_t)num_items, -1);
    std::vector<int> group_sizes;

    int num_groups = 0;

    for(int i = 0; i < num_items; i++) {
        if(x_groups[i] != -1) {
            continue;
        }

        x_groups[i] = num_groups;

        int group_size = 1;

        for(int j = i + 1; j < num_items; j++) {
            long long product = 1LL * xs[i] * xs[j];

            if(is_square(product)) {
                x_groups[j] = num_groups;

                group_size += 1;
            }
        }

        group_sizes.push_back(group_size);

        num_groups += 1;
    }

    /**
     * `num_placements[i][j]` stores the number of possible ways to place first (`i` + 1) groups so that there are `j`
     * pairs of "bad" neighbours (s.t. their product is a square)
     */
    std::vector<std::vector<int64_t>> num_placements(
            (size_t)num_groups + 1,
            std::vector<int64_t>((size_t)num_items, 0)
    );

    /**
     * If one group is placed, there's only one way to place it (order of elements within the group isn't counted), and
     * this will produce group_sizes[0] bad neighbour pairs
     */
    num_placements[0][group_sizes[0] - 1] = 1;

    int total_placed = group_sizes[0];

    binomial_calculator bc;

    const int64_t P = 1000 * 1000 * 1000 + 7;

    for(int i_group = 1; i_group < num_groups; i_group++) {
        for(int n_bad = 0; n_bad < total_placed; n_bad++) {
            for(int n_seg = 1; n_seg <= group_sizes[i_group]; n_seg++) {
                for(int n_elim = 0; n_elim <= std::min(n_bad, n_seg); n_elim++) {
                    /**
                     * Count the number of ways to divide group `i` into `n_seg` subsegments, then intersperse those
                     * segments among the bad neighbour pairs of the current placement, eliminating `n_elim` of them
                     */

                    num_placements[i_group][n_bad + group_sizes[i_group] - n_seg - n_elim] +=
                            num_placements[i_group - 1][n_bad]
                            // Number of ways to distribute elements of group `i` into `n_seg` segments
                            * bc.get_binomial(group_sizes[i_group] - 1, n_seg - 1) % P
                            // Number of ways to choose which bad pairs to eliminate
                            * bc.get_binomial(n_bad, n_elim) % P
                            // Number of ways to place the other segments (that don't break up bad pairs)
                            * bc.get_binomial(total_placed - 1 - n_bad + 2, n_seg - n_elim) % P;

                    num_placements[i_group][n_bad + group_sizes[i_group] - n_seg - n_elim] %= P;
                }
            }
        }

        total_placed += group_sizes[i_group];
    }

    int64_t result = num_placements[num_groups - 1][0];

    /**
     * Elements of every group can be permuted among themselves in any order
     */

    factorial_mod_p_calculator fact(P);

    for(int i = 0; i < num_groups; i++)
    {
        result *= fact.get_factorial(group_sizes[i]);
        result %= P;
    }

    std::cout << result << std::endl;
}
