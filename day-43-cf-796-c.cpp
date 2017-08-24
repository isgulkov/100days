#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_set>

class bank_network
{
    std::vector<std::vector<int>> adj_lists;
    std::vector<int> security;

    std::vector<int> eccentricity;

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

    void compute_eccentricity()
    {
        eccentricity.resize((size_t)num_nodes);

        std::vector<bool> visited((size_t)num_nodes, false);

        std::vector<int> this_layer;

        for(int u = 0; u < num_nodes; u++) {
            /**
             * Start from leaves
             */

            if(adj_lists[u].size() == 1) {
                this_layer.push_back(u);

                visited[u] = true;
            }
        }

        int i_current_layer = 0;

        std::vector<int> next_layer;

        while(!this_layer.empty()) {
            for(int u : this_layer) {
                eccentricity[u] = i_current_layer;

                for(int v : adj_lists[u]) {
                    if(!visited[v]) {
                        next_layer.push_back(v);

                        visited[v] = true;
                    }
                }
            }

            this_layer = next_layer;
            next_layer.clear();

            i_current_layer += 1;
        }
    }

public:
    bool can_be_hacked_with(int power)
    {
        if(eccentricity.empty()) {
            compute_eccentricity();
        }

        std::vector<int> most_secure_nodes { 0 };
        int greatest_security = security[0];

        for(int i = 0; i < num_nodes; i++) {
            if(security[i] > greatest_security) {
                greatest_security = security[i];

                most_secure_nodes.clear();

                most_secure_nodes.push_back(i);
            }
            else if(security[i] == greatest_security) {
                if(eccentricity[i] > eccentricity[most_secure_nodes[0]]) {
                    most_secure_nodes.clear();

                    most_secure_nodes.push_back(i);
                }
                else if(eccentricity[i] == eccentricity[most_secure_nodes[0]]) {
                    most_secure_nodes.push_back(i);
                }
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

    scanf("%d", &num_banks);

    bank_network b(num_banks);

    for(int i = 0; i < num_banks; i++) {
        int security;

        scanf("%d", &security);

        b.set_security(i, security);
    }

    for(int i = 0; i < num_banks - 1; i++) {
        int u, v;

        scanf("%d %d", &u, &v);

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

    printf("%d\n", l);
}
