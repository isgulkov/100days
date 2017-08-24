#include <iostream>
#include <vector>
#include <algorithm>

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


private:
    bool can_be_hacked_with(int u, int parent, int depth, int power)
    {
        int security_increase = depth <= 1 ? depth : 2;

        if(security[u] + security_increase > power) {
            return false;
        }

        bool result = true;

        for(int v : adj_lists[u]) {
            if(v == parent) {
                continue;
            }

            result &= can_be_hacked_with(v, u, depth + 1, power);
        }

        return result;
    }

public:
    bool can_be_hacked_with(int power)
    {
        int most_secure_node = 0;

        for(int i = 0; i < num_nodes; i++) {
            if(security[i] > security[most_secure_node]) {
                most_secure_node = i;
            }
        }

        return can_be_hacked_with(most_secure_node, -1, 0, power);
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

    int l = -1000 * 1000 * 1000;
    int r = 1000 * 1000 * 1000;

    while(l < r) {
        int mid = l + (r - l) / 2;

        if(b.can_be_hacked_with(mid)) {
            r = mid;
        }
        else {
            l = mid + 1;
        }
    }

    std::cout << l << std::endl;
}
