#include <iostream>
#include <vector>

int main()
{
    std::ios::sync_with_stdio(false);

    int num_flights, initial_delay;

    std::cin >> num_flights >> initial_delay;

    std::vector<int> unit_delay_costs((size_t)num_flights);

    for(int i = 0; i < num_flights; i++) {
        std::cin >> unit_delay_costs[i];
    }


}
