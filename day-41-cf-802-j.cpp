#include <iostream>
#include <vector>

class graph
{
    std::vector<std::vector<std::pair<int, int>>> adj_lists;

public:
    graph(int num_nodes) : adj_lists((size_t)num_nodes) { }

    void add_edge(int u, int v, int cost)
    {
        adj_lists[u].push_back(std::make_pair(v, cost));
        adj_lists[v].push_back(std::make_pair(u, cost));
    }

private:
    void max_journey_dfs(int u, int parent, int current_cost, int& max_cost)
    {
        if(current_cost > max_cost) {
            max_cost = current_cost;
        }

        for(std::pair<int, int> pair : adj_lists[u]) {
            int v = pair.first;

            if(v == parent) {
                continue;
            }

            int edge_cost = pair.second;

            max_journey_dfs(v, u, current_cost + edge_cost, max_cost);
        }
    }

public:
    int get_max_journey_cost(int start)
    {
        int max_cost = 0;

        max_journey_dfs(start, -1, 0, max_cost);

        return max_cost;
    }
};

int main()
{
    int num_nodes;

    std::cin >> num_nodes;

    graph g(num_nodes);

    for(int i = 0; i < num_nodes - 1; i++) {
        int u, v, cost;

        std::cin >> u >> v >> cost;

        g.add_edge(u, v, cost);
    }

    std::cout << g.get_max_journey_cost(0) << std::endl;
}
