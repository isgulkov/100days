#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

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

    int num_nodes;
    int num_edges;

public:
    graph(int num_nodes) : node_values((size_t)num_nodes), adj_lists((size_t)num_nodes), num_edges(0),
                           num_nodes(num_nodes) { }

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

private:
    bool make_sum_even(std::vector<int>& new_values)
    {
        /**
         * Check if it is possible make sum of the node values even (as has to be the sum of all node degrees in a
         * graph) by replacing "-1"s by "0"s and "1"s; and if it is, store the new node values in `new_values`
         */

        int current_remainder = 0;
        int num_negative_ones = 0;

        for(int i = 0; i < num_nodes; i++) {
            if(node_values[i] != -1) {
                current_remainder += node_values[i];
            }
            else {
                num_negative_ones += 1;
            }
        }

        current_remainder %= 2;

        if(current_remainder == 1 && num_negative_ones == 0) {
            return false;
        }
        else {
            new_values.resize((size_t)num_nodes);

            for(int i = 0; i < num_nodes; i++) {
                if(node_values[i] == -1) {
                    /**
                     * If the sum is odd, put just one "1" in some node
                     */

                    new_values[i] = current_remainder;

                    current_remainder = 0;
                }
                else {
                    new_values[i] = node_values[i];
                }
            }

            return true;
        }
    }

    void dfs_spanning_tree(int u, int parent, std::vector<int>& selected_edge_ids, std::unordered_set<int>& visited,
                           std::vector<int>& new_node_values)
    {
        visited.insert(u);

        for(int v : adj_lists[u]) {
            if(visited.find(v) != visited.end()) {
                continue;
            }

            dfs_spanning_tree(v, u, selected_edge_ids, visited, new_node_values);
        }

        if(new_node_values[u] == 1) {
            selected_edge_ids.push_back(edge_ids[std::make_pair(u, parent)]);

            new_node_values[parent] = (new_node_values[parent] + 1) % 2;
        }
    }

public:
    bool good_subset_possible(std::vector<int>& selected_edge_ids)
    {
        std::vector<int> evened_node_values;

        if(!make_sum_even(evened_node_values)) {
            return false;
        }

        std::unordered_set<int> visited;

        dfs_spanning_tree(0, -1, selected_edge_ids, visited, evened_node_values);

        return true;
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
            std::cout << (s + 1) << std::endl;
        }
    }
    else {
        std::cout << -1 << std::endl;
    }
}
