#include <iostream>
#include <vector>

class graph
{
    std::vector<std::vector<std::pair<int, int>>> adj_lists;

    int num_nodes;

public:
    graph(int num_nodes) : num_nodes(num_nodes), adj_lists((size_t)num_nodes) { }

    void add_edge(int u, int v, int weight)
    {
        adj_lists[u].push_back(std::make_pair(v, weight));
        adj_lists[v].push_back(std::make_pair(u, weight));
    }
};

int main()
{
    int num_nodes, num_edges;

    std::cin >> num_nodes >> num_edges;

    graph g(num_nodes);

    while(num_edges--) {
        int u, v, w;

        std::cin >> u >> v >> w;

        g.add_edge(u - 1, v - 1, w);
    }
}

