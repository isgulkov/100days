#include <iostream>
#include <vector>

class graph
{
    std::vector<std::vector<std::pair<int, int>>> adj_lists;

public:
    graph(int num_nodes) : adj_lists((size_t)num_nodes) { }

    void add_edge(int u, int v, int cost)
    {
        adj_lists[u].push_back(std::make_pair(v, cost));
        adj_lists[v].push_back(std::make_pair(u, cost));
    }
};

int main()
{
    int num_nodes;

    std::cin >> num_nodes;

    graph g(num_nodes);

    for(int i = 0; i < num_nodes - 1; i++) {
        int u, v, cost;

        std::cin >> u >> v >> cost;

        g.add_edge(u, v, cost);
    }

    
}
