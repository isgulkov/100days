#include <iostream>

class dogonyalkee_tree
{
    int num_nodes, bob_node;

public:
    dogonyalkee_tree(int num_nodes, int bob_node) : num_nodes(num_nodes), bob_node(bob_node) { }

    void add_edge(int u, int v)
    {

    }
};

int main()
{
    int num_nodes, bob_node;

    std::cin >> num_nodes >> bob_node;

    dogonyalkee_tree t(num_nodes, bob_node);

    for(int i = 0; i < num_nodes - 1; i++) {
        int u, v;

        std::cin >> u >> v;

        t.add_edge(u - 1, v - 1);
    }

    return 0;
}
