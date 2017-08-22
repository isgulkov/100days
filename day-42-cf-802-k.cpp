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

        int64_t max_total_through_cost = 0;

        int64_t min_through = 0;

        int64_t max_deadend_cost = 0;
        int64_t max_deadend_through = 0;

        /**
         * Select `max_visits` most costly subtrees to calculate the maximum cost that can be accumulated by going in a
         * and out of every sub-subtree
         */

        for(int i = 0; i < std::min((int)max_subtree_costs.size(), max_visits); i++) {
            std::pair<int64_t, int64_t> p = max_subtree_costs[max_subtree_costs.size() - i - 1];

            max_total_through_cost += p.first;

            if(p.second > max_deadend_cost) {
                /**
                 * Among the subtrees selected thus far, maintain both the costs of the one with the largest "dead end
                 * cost", so we can later substitute its through value for its dead end value in the final dead end sum
                 */
                max_deadend_cost = p.second;
                max_deadend_through = p.first;
            }

            /**
             * Maintain the smallest through value, so if we later find a subtree with the largest dead end value
             * outside the ones we selected, we can substitute that for this in the final dead end sum
             */

            min_through = p.first;
        }

        /**
         * See if there are any better candidates for the dead end subtree than ones that we have selected for their max
         * through value
         */
        for(int i = 0; i < max_subtree_costs.size(); i++) {
            std::pair<int64_t, int64_t> p = max_subtree_costs[i];

            if(p.second > max_deadend_cost) {
                max_deadend_cost = p.second;

                /**
                 * If there is one, we will substitute it for the subtree with the smallest through value we have
                 * selected
                 */
                max_deadend_through = min_through;
            }
        }

        int64_t max_total_deadend_cost = max_total_through_cost - max_deadend_through + max_deadend_cost;

        /**
         * Remove the subtree with the smallest through value if we can't afford it
         */
        if(max_subtree_costs.size() >= max_visits) {
            max_total_through_cost -= min_through;
        }

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
