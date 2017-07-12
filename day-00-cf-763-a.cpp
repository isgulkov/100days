#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    struct Graph
    {
    private:
        std::vector<std::vector<int>> adj_lists;
        std::vector<int> vertex_color;

        int num_nodes;

    public:
        Graph(int n) : num_nodes(n), adj_lists(n), vertex_color(n)
        {
            for(std::vector<int>& v : adj_lists) {
                v.reserve(100);
            }
        }

        void add_edge(int u, int v)
        {
            adj_lists[u].push_back(v);
            adj_lists[v].push_back(u);
        }

        void set_color(int v, int color)
        {
            vertex_color[v] = color;
        }

        /**
         * @return Pair of nodes that are adjacent and have different colors. If there is no such pair in the graph,
         * returns a pair of `-1`s
         */
        std::pair<int, int> get_discolored_edge()
        {
            for(int u = 0; u < num_nodes; u++) {
                for(int v : adj_lists[u]) {
                    if(vertex_color[u] != vertex_color[v]) {
                        return std::make_pair(u, v);
                    }
                }
            }

            return std::make_pair(-1, -1);
        };

    private:

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

    std::pair<int, int> discolored_edge = g.get_discolored_edge();

    if(discolored_edge.first == -1) {
        std::cout << "YES" << std::endl << 1 << std::endl;
    }
    else {
        std::cout << discolored_edge.first << " " << discolored_edge.second << std::endl;
    }



    return 0;
};
