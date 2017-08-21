#include <iostream>
#include <vector>
#include <unordered_set>

class graph
{
    std::vector<int> node_values;
    std::vector<std::vector<std::pair<int, int>>> adj_lists;

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
        /**
         * Store the sequential id of the edge together with the destination node
         */

        adj_lists[u].push_back(std::make_pair(v, num_edges));
        adj_lists[v].push_back(std::make_pair(u, num_edges));

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
                     * If the sum is odd, put just one "1" in any one node
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

    void dfs_spanning_tree(int u, int parent, int edge_id, std::vector<int>& selected_edge_ids, std::unordered_set<int>& visited,
                           std::vector<int>& new_node_values)
    {
        visited.insert(u);

        for(std::pair<int, int> p : adj_lists[u]) {
            int v = p.first;

            if(visited.find(v) != visited.end()) {
                continue;
            }

            dfs_spanning_tree(v, u, p.second, selected_edge_ids, visited, new_node_values);
        }

        if(new_node_values[u] == 1) {
            /**
             * Add the edge `parent` -> `u` to the resulting graph
             */
            selected_edge_ids.push_back(edge_id);

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

        dfs_spanning_tree(0, -1, -1, selected_edge_ids, visited, evened_node_values);

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
