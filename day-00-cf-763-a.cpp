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

        int num_edges;

    public:
        Graph(int n) : num_edges(n), adj_lists(n), vertex_color(n)
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

    for(int i = 0; i < num_edges; i++) {
        if(g.subtrees_color(i) >= -1) {
            std::cout << "YES" << std::endl;
            std::cout << (i + 1) << std::endl;

            return 0;
        }
    }

    std::cout << "NO" << std::endl;

    return 0;
};
