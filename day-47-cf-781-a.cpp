#include <iostream>
#include <vector>
#include <algorithm>

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

    int get_node_colors(std::vector<int>& node_colors)
    {
        node_colors.resize((size_t)num_nodes);

        colorize_nodes(0, -1, 0, -1, node_colors);

        return 1 + *std::max_element(node_colors.begin(), node_colors.end());
    }

private:
    void colorize_nodes(int u, int parent, int u_color, int parent_color, std::vector<int>& node_colors)
    {
        node_colors[u] = u_color;

        int other_color = 0;

        for(int v : adj_lists[u]) {
            if(v == parent) {
                continue;
            }

            while(other_color == u_color || other_color == parent_color) {
                other_color += 1;
            }

            colorize_nodes(v, u, other_color++, u_color, node_colors);
        }
    }
};

int main()
{
    int num_nodes;

    std::cin >> num_nodes;

    tree t(num_nodes);

    for(int i = 0; i < num_nodes - 1; i++) {
        int u, v;

        std::cin >> u >> v;

        t.add_edge(u - 1, v - 1);
    }

    std::vector<int> node_colors;

    std::cout << t.get_node_colors(node_colors) << std::endl;

    for(int c : node_colors) {
        std::cout << (c + 1) << " ";
    }

    std::cout << std::endl;
}
