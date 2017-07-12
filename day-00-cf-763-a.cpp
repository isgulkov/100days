#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

int main()
{
    struct Graph
    {
    private:
        std::vector<std::unordered_set<int>> adj_lists;
        std::vector<int> vertex_color;

        int num_nodes;

    public:
        Graph(int n) : num_nodes(n), adj_lists(n), vertex_color(n)
        {
            for(std::unordered_set<int>& v : adj_lists) {
                v.reserve(100);
            }
        }

        void add_edge(int u, int v)
        {
            adj_lists[u].insert(v);
            adj_lists[v].insert(u);
        }

        void set_color(int v, int color)
        {
            vertex_color[v] = color;
        }

        /**
         * Compacts the graph by merging all pairs of adjacent vertices that have the same color
         *
         * Time: O(n) (a least in a tree)
         */
        void compact()
        {
            for(int u = 0; u < num_nodes; u++) {
                std::vector<int> to_be_merged;

                for(int v : adj_lists[u]) {
                    if(vertex_color[u] == vertex_color[v]) {
                        to_be_merged.push_back(v);
                    }
                }

                for(int v : to_be_merged) {
                    merge_vertices(u, v);
                }
            }
        }

        /**
         * @return Index of the node that is adjacent to every other connected node in the tree. If such node doesn't
         * exits, return -1. If the has no nodes connected to other nodes (which means that there is only one node left
         * after the compaction operation), return 0
         */
        int get_totally_adjacent_node()
        {
            int num_connected_nodes = 0;

            for(std::unordered_set<int>& adjacent : adj_lists) {
                if(!adjacent.empty()) {
                    num_connected_nodes += 1;
                }
            }

            if(num_connected_nodes == 0) {
                return 0;
            }

            for(int v = 0; v < num_nodes; v++) {
                if((int)adj_lists[v].size() == num_connected_nodes - 1) {
                    return v;
                }
            }

            return -1;
        };

    private:
        /**
         * Merges `donor` vertex into `host` vertex, i.e.:
         * * connects all the vertices the `donor` node was previously connected to to the `host` node
         * * disconnects the `donor` node from every node
         * @param host The node for the `donor` node to be merged into
         * @param donor The node to be merged into the `host` node
         */
        void merge_vertices(int host, int donor)
        {
            adj_lists[host].erase(donor);

            for(int v : adj_lists[donor]) {
                if(v == host) {
                    continue;
                }

                adj_lists[host].insert(v);
                adj_lists[v].insert(host);

                adj_lists[v].erase(donor);
            }

            adj_lists[donor].clear();
        }
    };

    int num_edges;

    std::cin >> num_edges;

    Graph g(num_edges);

    for(int i = 0; i < num_edges - 1; i++) {
        int u, v;

        std::cin >> u >> v;

        g.add_edge(u - 1, v - 1);
    }

    for(int i = 0; i < num_edges; i++) {
        int c;

        std::cin >> c;

        g.set_color(i, c);
    }

    g.compact();

    int node = g.get_totally_adjacent_node();

    if(node == -1) {
        std::cout << "NO" << std::endl;
    }
    else {
        std::cout << "YES" << std::endl << node + 1 << std::endl;
    }

    return 0;
};
