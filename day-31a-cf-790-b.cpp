#include <iostream>
#include <vector>
#include <numeric>

class bank_network
{
    int num_nodes;
    int jump_distance;

    std::vector<std::vector<int>> adj_lists;

public:
    bank_network(int num_nodes, int jump_distance) : num_nodes(num_nodes), jump_distance(jump_distance),
                                             adj_lists((size_t)num_nodes) { }

    void add_edge(int u, int v)
    {
        adj_lists[u].push_back(v);
        adj_lists[v].push_back(u);
    }

    long long get_sum_of_jump_path_lengths()
    {
        /**
         * Length of a pth measured in jumps is equal to L = ceil(l / `jump_distance`), where l is regular length of the
         * path.
         *
         * Express that as (l + def(l, `jump_distance`)) / `jump_distance`, where def(a, b) is smallest non-negative
         * integer s.t. a + def(a, b) is divisible by b.
         *
         * Thus, Sum(L) for all paths is will be equal to: Sum(l) / k + Sum(def(l, `jump_distance`)) / k.
         */

        long long sum_paths = 0LL;
        long long total_deficit = 0LL;

        get_remainders_and_count_nodes(0, -1, sum_paths, total_deficit);

        return (sum_paths + total_deficit) / jump_distance;
    }

private:
    struct subtree_info
    {
        std::vector<long long> root_remainers;
        int node_count;

        subtree_info(int jump_distance) : root_remainers((size_t)jump_distance, 0) { }
    };

    subtree_info get_remainders_and_count_nodes(int u, int parent, long long& sum_paths, long long& total_deficit)
    {
        subtree_info result(jump_distance);

        result.node_count = 1;

        result.root_remainers[0] = 1;

        for(int v : adj_lists[u]) {
            if(v == parent) {
                continue;
            }

            subtree_info subtree_result = get_remainders_and_count_nodes(v, u, sum_paths, total_deficit);

            /**
             * Add to the sum of all path lengths the number of paths that go through edge "u -> v"
             */
            sum_paths += 1LL * subtree_result.node_count * (num_nodes - subtree_result.node_count);

            result.node_count += subtree_result.node_count;

            /**
             * For every path between a node in the `v` subtree and a node `u` or any node in all previous subtrees,
             * add to `total_deficit` how much needs to be added to its length for it to become divisible by
             * `jump_distance`
             */
            for(int i = 0; i < jump_distance; i++) {
                for(int j = 0; j < jump_distance; j++) {
                    long long deficit = (2 * jump_distance - (i + j + 1)) % jump_distance;

                    total_deficit += deficit * subtree_result.root_remainers[i] * result.root_remainers[j];
                }
            }

            for(int i = 0; i < jump_distance; i++) {
                result.root_remainers[(i + 1) % jump_distance] += subtree_result.root_remainers[i];
            }
        }

        return result;
    }
};

int main()
{
    int num_nodes, jump_distance;

    std::cin >> num_nodes >> jump_distance;

    bank_network t(num_nodes, jump_distance);

    for(int i = 0; i < num_nodes - 1; i++) {
        int u, v;

        std::cin >> u >> v;

        t.add_edge(u - 1, v - 1);
    }

    std::cout << t.get_sum_of_jump_path_lengths() << std::endl;
}
