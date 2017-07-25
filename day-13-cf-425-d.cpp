#include <iostream>

class lca_tree
{
    int num_nodes;

public:
    lca_tree(int num_nodes) : num_nodes(num_nodes) { }

    void add_edge(int u, int v)
    {

    }

    void hang_by(int u)
    {

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
