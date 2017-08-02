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

        *every_node_reachable_from_a_cycle = true; // TODO

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

long long get_lcm(std::vector<int>& xs)
{
    if(xs.size() == 1) {
        return xs[0];
    }

    int common_gcd = get_gcd(xs[0], xs[1]);

    for(int x : xs) {
        common_gcd = get_gcd(common_gcd, x);
    }

    long long product = 1;

    for(int x : xs) {
        product *= x;
    }

    return product / common_gcd;
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
        std::cout << get_lcm(cycle_ts) << std::endl;
    }
    else {
        std::cout << -1 << std::endl;
    }
}
