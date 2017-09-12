#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

class graph
{
    std::vector<std::vector<std::pair<int, int>>> adj_lists;

    int num_nodes;

public:
    graph(int num_nodes) : num_nodes(num_nodes), adj_lists((size_t)num_nodes) { }

    void add_edge(int u, int v, int weight)
    {
        adj_lists[u].push_back(std::make_pair(v, weight));
        adj_lists[v].push_back(std::make_pair(u, weight));
    }

    int get_minimum_route_cost(int u, int v)
    {
        /**
         * Get the cost of a some route from `u` to `v`. Because of the nature of XOR cost function, any route between
         * two vertices can be made to have another route's cost by traversing cycles if such exist in the graph
         */
        int some_route_cost = get_any_route_cost(u, v);

        /**
         * Get all possible cycle costs, as any cycle can be traversed in addition to any existing route with its cost
         * getting XOR'd into the route's cost. The cost of reaching the cycle from vertices of the initial route is
         * negated as it gets XOR'd twice
         */
        std::unordered_set<int> cycle_costs = get_all_cycle_costs();

        /**
         * Treating cycle costs as 32-bit vectors over Z/2, perform a Gaussian elimination on the cycle cost, thus
         * forming a basis of this vector system, which is needed for efficient route cost minimization
         */
        std::vector<int> basis = perform_gaussian_elimination(cycle_costs);

        /**
         * Zero out as many of the most significant bits of the route cost as possible
         */
        for(int i_b = 0, col = 0; i_b < basis.size() && col < 32; col++) {
            if(bit_from_left(some_route_cost, col) && bit_from_left(basis[i_b], col)) {
                some_route_cost ^= basis[i_b++];
            }
        }

        return some_route_cost;
    }

private:
    static std::vector<int> perform_gaussian_elimination(std::unordered_set<int> vectors)
    {
        /**
         * Perform gaussian elimination on Z/2 vectors presented in form of 32-bit integers
         */

        std::vector<int> vs;

        for(int v : vectors) {
            vs.push_back(v);
        }

        int first_untouched_row = 0;

        for(int col = 0; col < 32; col++) {
            int nonzero_row = -1;

            for(int i_row = first_untouched_row; i_row < vs.size(); i_row++) {
                if(bit_from_left(vs[i_row], col)) {
                    nonzero_row = i_row;
                    break;
                }
            }

            if(nonzero_row != -1) {
                std::swap(vs[first_untouched_row], vs[nonzero_row]);

                for(int i_row = 0; i_row < vs.size(); i_row++) {
                    if(i_row == first_untouched_row) {
                        continue;
                    }

                    if(bit_from_left(vs[i_row], col)) {
                        vs[i_row] ^= vs[first_untouched_row];
                    }
                }

                first_untouched_row += 1;
            }
        }

        /**
         * Remove zero vectors from the resulting basis
         */

        while(vs.back() == 0) {
            vs.pop_back();
        }

        return vs;
    }

    static bool bit_from_left(int x, int pos)
    {
        return ((x >> (31 - pos)) & 1) != 0;
    }

    int get_any_route_cost(int u, int v)
    {
        std::vector<bool> visited((size_t)num_nodes, false);

        return dfs_any_route(u, v, visited);
    }

    int dfs_any_route(int u, int target, std::vector<bool>& visited)
    {
        visited[u] = true;

        if(u == target) {
            return 0;
        }

        for(std::pair<int, int> pv : adj_lists[u]) {
            int v = pv.first;

            if(visited[v]) {
                continue;
            }


            int weight = pv.second;

            int v_result = dfs_any_route(v, target, visited);

            if(v_result != -1) {
                return weight ^ v_result;
            }
        }

        return -1;
    }

    std::unordered_set<int> get_all_cycle_costs()
    {
        std::vector<int> current_route_cost((size_t)num_nodes, -1); // Also functions as "visited"
        std::unordered_set<int> cycle_costs;

        current_route_cost[0] = 0;

        dfs_cycle_costs(0, current_route_cost, cycle_costs);

        return cycle_costs;
    }

    void dfs_cycle_costs(int u, std::vector<int>& current_route_cost, std::unordered_set<int>& cycle_costs)
    {
        for(std::pair<int, int> pv : adj_lists[u]) {
            int v = pv.first;
            int weight = pv.second;

            if(current_route_cost[v] != -1) {
                /**
                 * Reached a previously visited vertex -- found a cycle
                 */

                int cycle_cost = weight ^ current_route_cost[v] ^ current_route_cost[u];

                cycle_costs.insert(cycle_cost);
            }
            else {
                current_route_cost[v] = weight ^ current_route_cost[u];

                dfs_cycle_costs(v, current_route_cost, cycle_costs);
            }
        }
    }
};

int main()
{
    int num_nodes, num_edges;

    std::cin >> num_nodes >> num_edges;

    graph g(num_nodes);

    while(num_edges--) {
        int u, v, w;

        std::cin >> u >> v >> w;

        g.add_edge(u - 1, v - 1, w);
    }

    std::cout << g.get_minimum_route_cost(0, num_nodes - 1) << std::endl;
}

