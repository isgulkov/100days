#include <iostream>
#include <vector>
#include <unordered_map>

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        return h1 ^ h2;
    }
};

class graph
{
    std::vector<int> node_values;
    std::vector<std::vector<int>> adj_lists;

    std::unordered_map<std::pair<int, int>, int, pair_hash> edge_ids;

    int num_edges;

public:
    graph(int num_nodes) : node_values((size_t)num_nodes), adj_lists((size_t)num_nodes), num_edges(0) { }

    void set_node_value(int u, int value)
    {
        node_values[u] = value;
    }

    void add_edge(int u, int v)
    {
        adj_lists[u].push_back(v);
        adj_lists[v].push_back(u);

        edge_ids[std::make_pair(u, v)] = num_edges;
        edge_ids[std::make_pair(v, u)] = num_edges;

        num_edges += 1;
    }

    bool good_subset_possible(std::vector<int>& selected_edge_ids)
    {
        return false;
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

    std::vector<int> selected_edges;

    bool result = g.good_subset_possible(selected_edges);

    if(result) {
        std::cout << selected_edges.size() << std::endl;

        for(int s : selected_edges) {
            std::cout << (s - 1) << std::endl;
        }
    }
    else {
        std::cout << -1 << std::endl;
    }
}
