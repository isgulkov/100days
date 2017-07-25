#include <iostream>
#include <vector>
#include <algorithm>

class lca_tree
{
    int num_nodes;

    std::vector<std::vector<int>> children;

public:
    lca_tree(int num_nodes) : num_nodes(num_nodes), children((size_t)num_nodes) { }

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
     * "Hang" the tree by vertex `u` (so that all vectices become unidirectional and all nodes are reachable from `u`)
     * @param u The new root of the tree
     */
    void hang_by(int u)
    {
        for(int v : children[u]) {
            children[v].erase(std::remove(children[v].begin(), children[v].end(), u), children[v].end());

            hang_by(v);
        }
    }

    int common_edges(int u, int v, int w)
    {
        return 0;
    }
};

int main()
{
    int num_nodes, num_requests;

    std::cin >> num_nodes >> num_requests;

    lca_tree t(num_nodes);

    for(int u = 1; u < num_nodes; u++) {
        int v;

        std::cin >> v;

        t.add_edge(u, v - 1);
    }

    t.hang_by(0);

    for(int i = 0; i < num_requests; i++) {
        int u, v, w;

        std::cin >> u >> v >> w;

        std::cout << t.common_edges(u - 1, v - 1, w - 1) << std::endl;
    }
}
