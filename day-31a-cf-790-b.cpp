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

        std::vector<int> all_remainders((size_t)jump_distance, 0);

        get_remainders_and_count_nodes(0, -1, sum_paths, all_remainders);

        long long sum_remainders = 0LL;

        for(int i = 0; i < jump_distance; i++) {
            sum_remainders += i * all_remainders[i];
        }

        return sum_paths / jump_distance + (num_nodes * (num_nodes - 1) / 2 - sum_remainders) / jump_distance;
    }

private:
    struct remainders_and_counts
    {
        std::vector<int> remainders;

        int subtree_nodes;

        remainders_and_counts(int jump_distance) : remainders((size_t)jump_distance, 0) { }
    };

    remainders_and_counts get_remainders_and_count_nodes(int u, int parent, long long& sum_paths,
                                                         std::vector<int>& all_remainders)
    {
        remainders_and_counts result(jump_distance);

        result.subtree_nodes = 1;

        for(int v : adj_lists[u]) {
            if(v == parent) {
                continue;
            }

            std::cout << "---------- Going from " << (u + 1) << " into " << (v + 1) << std::endl;

            remainders_and_counts subtree_result = get_remainders_and_count_nodes(v, u, sum_paths, all_remainders);

            result.remainders[1] += 1;

            for(int i = 0; i < jump_distance; i++) {
                result.remainders[(i + 1) % jump_distance] += subtree_result.remainders[i];
            }

            /**
             * Add to the sum of all path lengths how many paths go through edge "u -> v"
             */
            sum_paths += subtree_result.subtree_nodes * (num_nodes - subtree_result.subtree_nodes);

            result.subtree_nodes += subtree_result.subtree_nodes;
        }

        std::vector<int> subtree_rems((size_t)jump_distance, 0);

        for(int i = 0; i < jump_distance; i++) {
            for(int j = 0; j < jump_distance; j++) {
                all_remainders[(i + j) % jump_distance] += result.remainders[i] * result.remainders[j];

                subtree_rems[(i + j) % jump_distance] += result.remainders[i] * result.remainders[j];
            }
        }

        std::cout << "Subtree " << (u + 1) << " result" << std::endl;

        std::cout << " Num nodes: " << result.subtree_nodes << std::endl;

        std::cout << " Root-going path rems: ";

        for(int x : result.remainders) {
            std::cout << x << " ";
        }

        std::cout << std::endl;

        std::cout << " Subtree-local path rems: ";

        for(int x : subtree_rems) {
            std::cout << x << " ";
        }

        std::cout << std::endl;

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
