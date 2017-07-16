#include <iostream>
#include <vector>
#include <unordered_set>

int main()
{
    struct Graph
    {
    private:
        int num_nodes;

        std::vector<std::unordered_set<int>> adj_lists;

    public:
        Graph(int n) : num_nodes(n), adj_lists(n) { }

        void add_edge(int u, int v)
        {
            adj_lists[u].insert(v);
            adj_lists[v].insert(u);
        }

        /**
         * Puts one node in between two other previously adjacent nodes, making both of them adjacent to the node, but
         * not to each other
         * @param rock A node adjacent to @param hard_place
         * @param u The node to be but in between two other odes
         * @param hard_place A node adjacent to @param rock
         */
        void put_in_between(int rock, int u, int hard_place)
        {
            /**
             * Disconnect the two nodes
             */
            adj_lists[rock].erase(hard_place);
            adj_lists[hard_place].erase(rock);

            /**
             * Connect the new node to the old two
             */
            add_edge(rock, u);
            add_edge(u, hard_place);
        }
    };

    int n, k;

    std::cin >> n >> k;

    std::cout << n << " " << k << std::endl;
}
