#include <iostream>
#include <stdio.h>
#include <vector>
#include <tuple>

int main()
{
    int num_trips, target_duration;

    std::cin >> num_trips >> target_duration;

    std::vector<std::tuple<int, int, int>> trips;

    for(int i = 0; i < num_trips; i++) {
        int start, end, cost;

        scanf("%d %d %d", &start, &end, &cost);

        trips.push_back(std::make_tuple(start, end, cost));
    }


}
