#include <iostream>
#include <vector>
#include <algorithm>

class dogonyalkee_tree
{
    int num_nodes, bob_node;

    std::vector<std::vector<int>> adj_lists;

    /**
     * For every subtree, maximum depth among its subtrees
     */
    std::vector<int> max_subtree_depth;

    /**
     * For every node, its depth relative to the root
     */
    std::vector<int> node_depth;

    /**
     * For every subtree, the depth at which `bob_node` lies in it, or -1 if `bob_node` isn't there
     */
    std::vector<int> relative_bob_depth;

    void hang_by(int u)
    {
        for(int v : adj_lists[u]) {
            adj_lists[v].erase(std::remove(adj_lists[v].begin(), adj_lists[v].end(), u));

            hang_by(v);
        }
    }

    void precompute_depth(int u, int depth)
    {
        node_depth[u] = depth;

        max_subtree_depth[u] = 0;

        for(int v : adj_lists[u]) {
            precompute_depth(v, depth + 1);

            if(max_subtree_depth[v] + 1 > max_subtree_depth[u]) {
                max_subtree_depth[u] = max_subtree_depth[v] + 1;
            }
        }
    }

    void compute_bob_depth(int u)
    {
        if(u == bob_node) {
            relative_bob_depth[u] = 0;
        }
        else {
            for(int v : adj_lists[u]) {
                compute_bob_depth(v);

                if(relative_bob_depth[v] != -1) {
                    relative_bob_depth[u] = relative_bob_depth[v] + 1;
                }
            }
        }
    }

public:
    dogonyalkee_tree(int num_nodes, int bob_node) : num_nodes(num_nodes), bob_node(bob_node),
                                                    adj_lists((size_t)num_nodes), max_subtree_depth((size_t)num_nodes),
                                                    node_depth((size_t)num_nodes),
                                                    relative_bob_depth((size_t)num_nodes, -1) { }

    void add_edge(int u, int v)
    {
        adj_lists[u].push_back(v);
        adj_lists[v].push_back(u);
    }

    int get_answer()
    {
        hang_by(0);

        precompute_depth(0, 0);

        compute_bob_depth(0);

        /**
         * Find the deepest subtree bob can get into before before Alice gets to the node next to its respective root.
         * Bob's strategy is then to get into that subtree and follow the deepest route
         */

        int best_subtree = bob_node, subtree = 0;

        while(relative_bob_depth[subtree] != -1) {
            if(node_depth[subtree] - relative_bob_depth[subtree] >= 1) {
                /**
                 * If bob can get into this subtree before alice gets him, choose this subtree as best subtree and exit — no
                 * need to consider deeper subtrees as they will only be shallower
                 */

                best_subtree = subtree;
                break;
            }

            /**
             * Go into the the subtree that has bob in it. If there's no such subtree (we are at the bob node), choose
             * any and the loop will end
             */

            for(int v : adj_lists[subtree]) {
                subtree = v;

                if(relative_bob_depth[v] != -1) {
                    break;
                }
            }
        }

        return 2 * (node_depth[best_subtree] + max_subtree_depth[best_subtree]);
    }
};

int main()
{
    int num_nodes, bob_node;

    std::cin >> num_nodes >> bob_node;

    dogonyalkee_tree t(num_nodes, bob_node - 1);

    for(int i = 0; i < num_nodes - 1; i++) {
        int u, v;

        std::cin >> u >> v;

        t.add_edge(u - 1, v - 1);
    }

    std::cout << t.get_answer() << std::endl;

    return 0;
}
