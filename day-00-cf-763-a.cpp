#include <iostream>
#include <vector>
#include <unordered_set>

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
            adj_lists[host].erase(std::remove(adj_lists[host].begin(), adj_lists[host].end(), donor));

            for(int v : adj_lists[donor]) {
                if(v == host) {
                    continue;
                }

                adj_lists[host].push_back(v);
                adj_lists[v].push_back(host);

                adj_lists[v].erase(std::remove(adj_lists[v].begin(), adj_lists[v].end(), donor));
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

    g.hui();

    g.merge_vertices(1, 0);

    g.hui();

    std::cout << "NO" << std::endl;

    return 0;
};
