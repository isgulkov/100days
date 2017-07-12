#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

int main()
{
    struct Graph
    {
    private:
        std::vector<std::vector<int>> adj_lists;
        std::vector<int> node_color;

        int num_nodes;

    public:
        Graph(int n) : num_nodes(n), adj_lists(n), node_color(n)
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
            node_color[v] = color;
        }

        /**
         * @return Pair of nodes that are adjacent and have different colors. If there is no such pair in the graph,
         * returns a pair of `-1`s
         */
        std::pair<int, int> get_discolored_edge()
        {
            for(int u = 0; u < num_nodes; u++) {
                for(int v : adj_lists[u]) {
                    if(node_color[u] != node_color[v]) {
                        return std::make_pair(u, v);
                    }
                }
            }

            return std::make_pair(-1, -1);
        };

        bool no_discolored_subtrees(int u)
        {
            for(int v : adj_lists[u]) {
                std::unordered_set<int> visited;

                visited.insert(u);

                if(get_subtree_color(v, visited) == -1) {
                    return false;
                }
            }

            return true;
        }

    private:
        /**
         * @param u The root node of the subtree
         * @param visited Set of visited nodes that is needed for tree traversal as the actual graph structure in this
         * implementation is a bidirected graph
         * @return The color that all the nodes of the subtree have. If there are nodes with different colors in the
         * subtree, return -1
         */
        int get_subtree_color(int u, std::unordered_set<int> visited)
        {
            visited.insert(u);

            for(int v : adj_lists[u]) {
                if(visited.find(v) != visited.end()) {
                    continue;
                }

                if(get_subtree_color(v, visited) != node_color[u]) {
                    return -1;
                }
            }

            return node_color[u];
        }
    };

    int num_nodes;

    std::cin >> num_nodes;

    Graph g(num_nodes);

    for(int i = 0; i < num_nodes - 1; i++) {
        int u, v;

        std::cin >> u >> v;

        g.add_edge(u - 1, v - 1);
    }

    for(int i = 0; i < num_nodes; i++) {
        int c;

        std::cin >> c;

        g.set_color(i, c);
    }

    std::pair<int, int> discolored_edge = g.get_discolored_edge();

    int result = -1;

    if(discolored_edge.first == -1) {
        result = 1;
    } else if(g.no_discolored_subtrees(discolored_edge.first)) {
        result = discolored_edge.first;
    } else if(g.no_discolored_subtrees(discolored_edge.second)) {
        result = discolored_edge.second;
    }

    if(result != -1) {
        std::cout << "YES" << std::endl << result + 1 << std::endl;
    }
    else {
        std::cout << "NO" << std::endl;
    }

    return 0;
};
