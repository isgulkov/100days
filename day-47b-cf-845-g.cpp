#include <iostream>
#include <vector>
#include <unordered_set>

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
        std::unordered_set<int> cycle_costs = get_all_cycle_costs();

        int some_route_cost = get_any_route_cost(u, v);

        // TODO: minimize route cost by xoring it with some cycle costs

        return some_route_cost;
    }

private:
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
                 * Found a cycle
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

