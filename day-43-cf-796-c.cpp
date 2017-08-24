#include <iostream>
#include <vector>

class bank_network
{
    std::vector<std::vector<int>> adj_lists;
    std::vector<int> security;

    int num_nodes;

public:
    bank_network(int num_nodes) : num_nodes(num_nodes), adj_lists((size_t)num_nodes), security((size_t)num_nodes) { }

    void add_edge(int u, int v)
    {
        adj_lists[u].push_back(v);
        adj_lists[v].push_back(u);
    }

    void set_security(int u, int value)
    {
        security[u] = value;
    }
};

int main()
{
    int num_banks;

    std::cin >> num_banks;

    bank_network b(num_banks);

    for(int i = 0; i < num_banks; i++) {
        int security;

        std::cin >> security;

        b.set_security(i, security);
    }

    for(int i = 0; i < num_banks - 1; i++) {
        int u, v;

        std::cin >> u >> v;

        b.add_edge(u - 1, v - 1);
    }


}
