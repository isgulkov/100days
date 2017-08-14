#include <iostream>
#include <vector>

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
};

int main()
{
    int num_nodes, jump_distance;

    std::cin >> num_nodes >> jump_distance;

    tree t(num_nodes, jump_distance);

    for(int i = 0; i < num_nodes; i++) {
        int u, v;

        std::cin >> u >> v;

        t.add_edge(u - 1, v - 1);
    }

    
}
