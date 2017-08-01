#include <iostream>

class oriented_graph
{
    int num_nodes;

public:
    oriented_graph(int num_nodes) : num_nodes(num_nodes) { }

    void add_edge(int u, int v)
    {

    }
};

int main()
{
    int n;

    std::cin >> n;

    oriented_graph g;

    for(int u = 0; u < n; u++) {
        int v;

        std::cin >> v;

        g.add_edge(u, v - 1);
    }
}
