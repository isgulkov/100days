#include <iostream>
#include <vector>
#include <map>

int main()
{
    std::ios::sync_with_stdio(false);

    int num_flights, initial_delay;

    std::cin >> num_flights >> initial_delay;

    std::vector<int> unit_delay_costs((size_t)num_flights);

    for(int i = 0; i < num_flights; i++) {
        std::cin >> unit_delay_costs[i];
    }

    int64_t total_delay_cost = 0LL;

    /**
     * We need to minimize the following expression:
     *   Sum(c_i * (t_i - i)),
     * where for a flight with scheduled departuare time `i`, `c_i` is the unit cost of delay of the flight and `t_i` is
     * the actual departure time. Rearrange the expression:
     *   Sum(c_i * t_i) - Sum(c_i * i),
     * where the second term is fixed and is calculated below, and the first term can be minimized eagerly.
     */

    for(int i = 0; i < num_flights; i++) {
        total_delay_cost -= 1LL * unit_delay_costs[i] * (i + 1);
    }

    std::multimap<int, int> flights_by_cost;

    for(int i = 0; i < initial_delay; i++) {
        flights_by_cost.insert(std::make_pair(unit_delay_costs[i], i));
    }

    std::vector<int> departure_time((size_t)num_flights);

    for(int t = initial_delay; t < num_flights + initial_delay; t++) {
        /**
         * For each departure time `t` find a flight that hasn't been selected for any previous `t`s and has the highest
         * unit cost among such.
         *
         * Suppose the following:
         * * flight `i` is selected on step `t1`;
         * * flight `j` is selected on step `t2`;
         * * `t1` < `t2`.
         * It can be shown that by choosing flights eagerly in the proposed way, these two flights will chosen in the
         * order that yields minimal total delay cost:
         * * if `j` > `t1`, `i` and `j` can't be swapped;
         * * if `j` <= `t1`, than `i` and `j` a selection can be made where `i` and `j` are swapped. Though only the
         *   selection where `i` >= `j` will be chosen and this selection is the one that contributes the smaller amount
         *   to the total delay cost, as from
         *     `i` >= `j`
         *     `t1` < `t2`
         *   trivially follows that
         *     `t1` * `i` + `t2` * `j` <= `t1` * `j` + `t2` * `i`.
         */

        if(t < num_flights) {
            flights_by_cost.insert(std::make_pair(unit_delay_costs[t], t));
        }

        auto biggest_element = flights_by_cost.end();
        biggest_element--;

        int max_i = biggest_element->second;

        flights_by_cost.erase(biggest_element);

        departure_time[max_i] = t;
        total_delay_cost += 1LL * unit_delay_costs[max_i] * (t + 1);
    }

    std::cout << total_delay_cost << std::endl;

    for(int t : departure_time) {
        std::cout << (t + 1) << " ";
    }

    std::cout << std::endl;
}
