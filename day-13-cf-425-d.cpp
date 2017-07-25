#include <iostream>
#include <vector>
#include <algorithm>

class lca_tree
{
    size_t num_nodes;

    std::vector<std::vector<int>> children;

    std::vector<int> visit_order;
    std::vector<int> time_in;
    std::vector<int> height;

public:
    lca_tree(size_t num_nodes) : num_nodes(num_nodes), children(num_nodes), time_in(num_nodes), height(num_nodes) { }

    void pidor()
    {
        for(int u = 0; u < num_nodes; u++) {
            std::cout << u << ": ";

            for(int v : children[u]) {
                std::cout << v << " ";
            }

            std::cout << std::endl;
        }
    }

    void add_edge(int u, int v)
    {
        children[u].push_back(v);
        children[v].push_back(u);
    }

    /**
     * "Hang" the tree by vertex `u` (so that all vectices become unidirectional and all nodes are reachable from `u`),
     * and also preprocessed the tree for least-common-ancestor requests
     * @param u The new root of the tree
     */
    void hang_by_and_preprocess_lca(int u)
    {
        hang_by(u);

        preprocess_lca(u);
    }

private:
    void hang_by(int u)
    {
        for(int v : children[u]) {
            children[v].erase(std::remove(children[v].begin(), children[v].end(), u), children[v].end());

            hang_by(v);
        }
    }

    void preprocess_lca(int root)
    {
        visit_order.reserve(2 * num_nodes);

        record_visit_order(root);

        for(int i = 0; i < num_nodes; i++) {
            time_in[visit_order[i]] = i;
        }

        record_height(root, 0);
    }

    void record_visit_order(int u)
    {
        visit_order.push_back(u);

        for(int v : children[u]) {
            record_visit_order(v);

            visit_order.push_back(u);
        }
    }

    void record_height(int u, int current_height)
    {
        height[u] = current_height;

        for(int v : children[u]) {
            record_height(v, current_height + 1);
        }
    }

public:
    int common_edges(int u, int v, int w)
    {
        return 0;
    }
};

int main()
{
    size_t num_nodes, num_requests;

    std::cin >> num_nodes >> num_requests;

    lca_tree t(num_nodes);

    for(int u = 1; u < num_nodes; u++) {
        int v;

        std::cin >> v;

        t.add_edge(u, v - 1);
    }

    t.hang_by_and_preprocess_lca(0);

    for(int i = 0; i < num_requests; i++) {
        int u, v, w;

        std::cin >> u >> v >> w;

        std::cout << t.common_edges(u - 1, v - 1, w - 1) << std::endl;
    }
}
