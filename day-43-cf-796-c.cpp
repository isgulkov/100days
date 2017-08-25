#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_set>

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

public:
    bool can_be_hacked_with(int power)
    {
        /**
         * Collect vector of nodes that are "not completely hackable" (i.e. can't be hacked if distance from the
         * original hack to them is 2 or greater)
         */

        std::vector<int> not_completely_hackable;

        for(int u = 0; u < num_nodes; u++) {
            if(security[u] + 2 > power) {
                not_completely_hackable.push_back(u);
            }
        }

        for(int u = 0; u < num_nodes; u++) {
            /**
             * See if the node and all its neighbours:
             * * are hackable at the current `power`;
             * * represent the whole "not completely hackable" set.
             */

            if(security[u] > power) {
                continue;
            }

            int nch_neighourhood = security[u] + 2 > power;

            for(int v : adj_lists[u]) {
                if(security[v] + 1 > power) {
                    continue;
                }

                if(security[v] + 2 > power) {
                    nch_neighourhood += 1;
                }
            }

            if(nch_neighourhood == not_completely_hackable.size()) {
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
