#include <iostream>
#include <vector>
#include <algorithm>

class graph
{
    std::vector<std::vector<std::pair<int, int>>> adj_lists;

    int max_visits;

public:
    graph(int num_nodes, int max_visits) : adj_lists((size_t)num_nodes), max_visits(max_visits) { }

    void add_edge(int u, int v, int cost)
    {
        adj_lists[u].push_back(std::make_pair(v, cost));
        adj_lists[v].push_back(std::make_pair(u, cost));
    }

private:
    /**
     * For subtree `u` return pair of values:
     * * maximum cost achievable by traversing the subtree and going out of it;
     * * maximum cost achievable by traversing the subtree and staying in it.
     */
    std::pair<int64_t, int64_t> get_max_subtree_cost(int u, int parent)
    {
        std::vector<std::pair<int64_t, int64_t>> max_subtree_costs;

        for(std::pair<int, int> pair : adj_lists[u]) {
            int v = pair.first;

            if(v == parent) {
                continue;
            }

            int edge_cost = pair.second;

            std::pair<int64_t, int64_t> subtree_result = get_max_subtree_cost(v, u);

            max_subtree_costs.push_back(
                    std::make_pair(subtree_result.first + edge_cost, subtree_result.second + edge_cost)
            );
        }

        std::sort(max_subtree_costs.begin(), max_subtree_costs.end());
        std::reverse(max_subtree_costs.begin(), max_subtree_costs.end());

        /**
         * Select at most `max_visits` - 1 best through subtrees (s.t. we can visit all them and come back out)
         */
        int64_t max_total_through_cost = 0;

        for(int i = 0; i < std::min((int)max_subtree_costs.size(), max_visits - 1); i++) {
            std::pair<int64_t, int64_t> p = max_subtree_costs[i];

            max_total_through_cost += p.first;
        }

        int64_t max_total_deadend_cost = 0;

        /**
         * Select the best dead end subtree (s.t. we end up in that subtree in the end)
         */
        for(int i = 0; i < max_subtree_costs.size(); i++) {
            std::pair<int64_t, int64_t>& p = max_subtree_costs[i];

            int64_t max_total_deadend_with_this;

            if(i < std::min((int)max_subtree_costs.size(), max_visits - 1)) {
                /**
                 * If this subtree is one of the best through ones, add make this one dead end instead of through and
                 * add another best through one if available
                 */

                max_total_deadend_with_this = max_total_through_cost - p.first + p.second;

                if(max_subtree_costs.size() >= max_visits) {
                    max_total_deadend_with_this += max_subtree_costs[max_visits - 1].first;
                }
            }
            else {
                /**
                 * If this subtree is not one of the best through ones, just add it to the pile
                 */

                max_total_deadend_with_this = max_total_through_cost + p.second;
            }

            if(max_total_deadend_with_this > max_total_deadend_cost) {
                max_total_deadend_cost = max_total_deadend_with_this;
            }
        }

        /**
         * Remove the subtree with the smallest through value if we can't afford it
         */

        return std::make_pair(max_total_through_cost, max_total_deadend_cost);
    }

public:
    int64_t get_max_journey_cost(int start)
    {
        return get_max_subtree_cost(start, -1).second;
    }
};

int main()
{
    int num_nodes, max_visits;

    std::cin >> num_nodes >> max_visits;

    graph g(num_nodes, max_visits);

    for(int i = 0; i < num_nodes - 1; i++) {
        int u, v, cost;

        std::cin >> u >> v >> cost;

        g.add_edge(u, v, cost);
    }

    std::cout << g.get_max_journey_cost(0) << std::endl;
}
