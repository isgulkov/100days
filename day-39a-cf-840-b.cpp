#include <iostream>
#include <vector>

class graph
{
    std::vector<int> node_values;
    std::vector<std::vector<int>> adj_lists;

public:
    graph(int num_nodes) : node_values((size_t)num_nodes), adj_lists((size_t)num_nodes) { }

    void set_node_value(int u, int value)
    {
        node_values[u] = value;
    }

    void add_edge(int u, int v)
    {
        adj_lists[u].push_back(v);
        adj_lists[v].push_back(u);
    }
};

int main()
{
    int num_nodes, num_edges;

    std::cin >> num_nodes >> num_edges;

    graph g(num_nodes);

    for(int u = 0; u < num_nodes; u++) {
        int d;

        std::cin >> d;

        g.set_node_value(u, d);
    }

    for(int i = 0; i < num_edges; i++) {
        int u, v;

        std::cin >> u >> v;

        g.add_edge(u - 1, v - 1);
    }

    
}
