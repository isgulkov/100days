#include <iostream>
#include <vector>

class union_find
{
    int num_nodes;
    int num_components;

    std::vector<int> parent;

    int find(int u)
    {
        if(u == parent[u]) {
            return u;
        }
        else {
            return parent[u] = find(parent[u]);
        }
    }

public:
    union_find(int n) : num_nodes(n), num_components(n), parent((size_t)n)
    {
        for(int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    bool merge_components(int u, int v)
    {
        if(find(u) != find(v)) {
            parent[parent[u]] = v;

            num_components -= 1;

            return true;
        }
        else {
            return false;
        }
    }

    bool has_only_one_component()
    {
        return num_components == 1;
    }
};

int main()
{
    int n;

    std::cin >> n;

    union_find c(n);

    int total_cost = 0;

    /**
     * Add in all edges of cost 0
     */
    for(int u = 1; u <= n / 2; u++) {
        int v = n + 1 - u;

        c.merge_components(u - 1, v - 1);
    }

    /**
     * Add all adges in order of increasing cost
     */
    for(int edge_cost = 1; !c.has_only_one_component(); edge_cost++) {
        /**
         * Add edges of cost `edge_cost`:
         */

        /**
         * ...edges s.t. u + v = `edge_cost`
         */
        for(int u = 1; u < edge_cost; u++) {
            int v = edge_cost - u;

            if(c.merge_components(u - 1, v - 1)) {
                total_cost += edge_cost;
            }
        }

        /**
         * ...edges s.t. u + v = (n + 1) + `edge_cost`
         */
        for(int u = edge_cost + 1; u <= n; u++) {
            int v = (n + 1) + edge_cost - u;

            if(c.merge_components(u - 1, v - 1)) {
                total_cost += edge_cost;
            }
        }
    }

    std::cout << total_cost << std::endl;
}
