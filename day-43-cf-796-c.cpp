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

        for(int v : adj_lists[u]) {
            if(v == parent) {
                continue;
            }

            if(!can_be_hacked_with(v, u, depth + 1, power)) {
                return false;
            }
        }

        return true;
    }

public:
    bool can_be_hacked_with(int power)
    {
        std::vector<int> most_secure_nodes { 0 };
        int greatest_security = security[0];

        for(int i = 0; i < num_nodes; i++) {
            if(security[i] > greatest_security) {
                greatest_security = security[i];

                most_secure_nodes.clear();

                most_secure_nodes.push_back(i);
            }
            else if(security[i] == greatest_security) {
                most_secure_nodes.push_back(i);
            }
        }

        for(int u : most_secure_nodes) {
            if(can_be_hacked_with(u, -1, 0, power)) {
                return true;
            }
        }

        return false;
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

    int l = INT32_MIN / 2;
    int r = INT32_MAX / 2;

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
