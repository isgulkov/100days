#include <iostream>
#include <vector>
#include <numeric>

class tree
{
    int num_nodes;
    int jump_distance;

    std::vector<std::vector<int>> adj_lists;

public:
    tree(int num_nodes, int jump_distance) : num_nodes(num_nodes), jump_distance(jump_distance),
                                             adj_lists((size_t)num_nodes) { }

    void add_edge(int u, int v)
    {
        adj_lists[u].push_back(v);
        adj_lists[v].push_back(u);
    }

    long long get_sum_of_jump_path_lengths()
    {
        long long sum_paths = 0LL;
        long long total_needs = 0LL;

        subtree_info tree_result = get_remainders_and_count_nodes(0, -1, 0, sum_paths, total_needs);

        return (sum_paths + total_needs) / jump_distance;
    }

private:
    struct subtree_info
    {
        std::vector<int> root_remainers;

        int node_count;

        subtree_info(int jump_distance) : root_remainers((size_t)jump_distance, 0) { }
    };

    subtree_info get_remainders_and_count_nodes(int u, int parent, int depth, long long& sum_paths, long long& total_needs)
    {
        subtree_info result(jump_distance);

        result.node_count = 1;

        for(int v : adj_lists[u]) {
            if(v == parent) {
                continue;
            }

            subtree_info subtree_result = get_remainders_and_count_nodes(v, u, depth + 1, sum_paths, total_needs);

            /**
             * Add to the sum of all path lengths how many paths go through edge "u -> v"
             */
            sum_paths += subtree_result.node_count * (num_nodes - subtree_result.node_count);

            result.node_count += subtree_result.node_count;

            for(int i = 0; i < jump_distance; i++) {
                for(int j = 0; j < jump_distance; j++) {
                    int needs = jump_distance - ((i + j - 2 * depth) % jump_distance + jump_distance) % jump_distance;

                    total_needs += needs * subtree_result.root_remainers[i] * result.root_remainers[j];
                }
            }

            for(int i = 0; i < jump_distance; i++) {
                result.root_remainers[(i + 1) % jump_distance] += subtree_result.root_remainers[i];
            }
        }

        result.root_remainers[1 % jump_distance] += 1;

        return result;
    }
};

int main()
{
    int num_nodes, jump_distance;

    std::cin >> num_nodes >> jump_distance;

    tree t(num_nodes, jump_distance);

    for(int i = 0; i < num_nodes - 1; i++) {
        int u, v;

        std::cin >> u >> v;

        t.add_edge(u - 1, v - 1);
    }

    std::cout << t.get_sum_of_jump_path_lengths() << std::endl;
}
