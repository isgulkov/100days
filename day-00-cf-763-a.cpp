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

        /**
         * Returns the color of all subtrees of the @param u tree
         * @return If all the subtrees of the @param u tree have the same color, returns such color.
         * If different subtrees of the @param u tree have different colors, returns -1.
         * If any of the subtrees are discolored, returns -2.
         */
        int subtrees_color(int u)
        {
            std::vector<bool> visited(num_edges, false);

            return subtrees_color(u, visited);
        }

    private:
        int subtrees_color(int u, std::vector<bool>& visited)
        {
            /*
             * Set the current subtrees color to the value `-3` which signifies that no colored subtrees of the current
             * tree were processed
             */
            int current_color = -3;

            visited[u] = true;

            for(int v : adj_lists[u]) {
                if(visited[v]) {
                    continue;
                }

                int v_color = subtrees_color(v, visited);

                switch(v_color) {
                    case -2:
                        return -2;
                    case -1:
                        return -2;
                    default:
                        if(v_color != vertex_color[v]) {
                            return -2;
                        }
                        else if(current_color == -3) {
                            current_color = v_color;
                        }
                        else if(current_color != v_color) {
                            return -1;
                        }
                }
            }

            if(current_color == -3) {
                return vertex_color[u];
            }
            else {
                return current_color;
            }
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
