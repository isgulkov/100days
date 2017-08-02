#include <iostream>
#include <vector>
#include <algorithm>

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

    std::vector<int> get_cycle_lengths(bool* every_node_reachable_from_a_cycle)
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

        std::vector<bool> reachable((size_t)num_nodes, false);

        for(int v : adj_list) {
            reachable[v] = true;
        }

        *every_node_reachable_from_a_cycle = std::all_of(reachable.begin(), reachable.end(), [](bool b) { return b; });

        return cycle_lengths;
    }
};

int get_gcd(int a, int b)
{
    if(a < b) {
        std::swap(a, b);
    }

    if(b == 0) {
        return a;
    }
    else {
        return get_gcd(b, a % b);
    }
}

int get_lcm(int a, int b)
{
    return a * b / get_gcd(a, b);
}

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

    bool every_node_reachable;

    std::vector<int> cycle_ts = g.get_cycle_lengths(&every_node_reachable);

    for(int& t : cycle_ts) {
        if(t % 2 == 0) {
            t /= 2;
        }
    }

    if(every_node_reachable) {
        int common_lcm = 1;

        for(int t : cycle_ts) {
            common_lcm = get_lcm(common_lcm, t);
        }

        std::cout << common_lcm << std::endl;
    }
    else {
        std::cout << -1 << std::endl;
    }
}
