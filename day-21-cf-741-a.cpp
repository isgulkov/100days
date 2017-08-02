#include <iostream>
#include <vector>

class oriented_graph
{
    int num_nodes;

    std::vector<int> adj_list;

    int get_cycle_length(int u, int depth, std::vector<int>& depths, std::vector<int>& colors)
    {
        depths[u] = depth;
        colors[u] = 1;

        int v = adj_list[u];

        int cycle_length;

        if(colors[v] == 1) {
            cycle_length = depths[u] - depths[v] + 1;
        }
        else if(colors[v] == 2) {
            cycle_length = 0;
        }
        else {
            cycle_length = get_cycle_length(v, depth + 1, depths, colors);
        }

        colors[u] = 2;

        return cycle_length;
    }

public:
    oriented_graph(int num_nodes) : num_nodes(num_nodes), adj_list((size_t)num_nodes) { }

    void set_edge(int u, int v)
    {
        adj_list[u] = v;
    }

    std::vector<int> get_cycle_lengths()
    {
        std::vector<int> cycle_lengths;

        std::vector<int> colors((size_t)num_nodes, 0);
        std::vector<int> depths((size_t)num_nodes, 0);

        for(int u = 0; u < num_nodes; u++) {
            if(colors[u] == 2) {
                continue;
            }

            int cycle_length = get_cycle_length(u, 0, depths, colors);

            if(cycle_length != 0) {
                cycle_lengths.push_back(cycle_length);
            }
        }

        return cycle_lengths;
    }
};

int main()
{
    int num_nodes;

    std::cin >> num_nodes;

    oriented_graph g(num_nodes);

    for(int u = 0; u < num_nodes; u++) {
        int v;

        std::cin >> v;

        g.set_edge(u, v - 1);
    }

    int min_t = INT32_MAX;

    for(int cycle_length : g.get_cycle_lengths()) {
        if(cycle_length == 1) {
            continue; // Actually something should be done here
        }

        if(cycle_length % 2 == 0 && cycle_length / 2 < min_t) {
            min_t = cycle_length / 2;
        }

        if(cycle_length % 2 == 1 && cycle_length < min_t) {
            min_t = cycle_length;
        }
    }

    if(min_t != INT32_MAX) {
        std::cout << min_t << std::endl;
    }
    else {
        std::cout << -1 << std::endl;
    }
}
