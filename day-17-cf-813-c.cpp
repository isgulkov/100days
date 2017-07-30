#include <iostream>
#include <vector>
#include <algorithm>

class dogonyalkee_tree
{
    int num_nodes, bob_node;

    std::vector<std::vector<int>> adj_lists;

    void hang_by(int u)
    {
        for(int v : adj_lists[u]) {
            adj_lists[v].erase(std::remove(adj_lists[v].begin(), adj_lists[v].end(), u));

            hang_by(v);
        }
    }

public:
    dogonyalkee_tree(int num_nodes, int bob_node) : num_nodes(num_nodes), bob_node(bob_node),
                                                    adj_lists((size_t)num_nodes) { }

    void add_edge(int u, int v)
    {
        adj_lists[u].push_back(v);
        adj_lists[v].push_back(u);
    }

    int get_answer()
    {
        hang_by(0);

        return 1337;
    }
};

int main()
{
    int num_nodes, bob_node;

    std::cin >> num_nodes >> bob_node;

    dogonyalkee_tree t(num_nodes, bob_node - 1);

    for(int i = 0; i < num_nodes - 1; i++) {
        int u, v;

        std::cin >> u >> v;

        t.add_edge(u - 1, v - 1);
    }

    std::cout << t.get_answer() << std::endl;

    return 0;
}
