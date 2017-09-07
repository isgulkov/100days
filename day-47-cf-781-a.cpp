#include <iostream>
#include <vector>

class tree
{
    std::vector<std::vector<int>> adj_lists;

    int num_nodes;

public:
    tree(int num_nodes) : num_nodes(num_nodes), adj_lists((size_t)num_nodes) { }

    void add_edge(int u, int v)
    {
        adj_lists[u].push_back(v);
        adj_lists[v].push_back(u);
    }
};

int main()
{
    int num_nodes;

    std::cin >> num_nodes;

    tree t(num_nodes);

    for(int i = 0; i < num_nodes; i++) {
        int u, v;

        std::cin >> u >> v;

        t.add_edge(u - 1, v - 1);
    }


}
