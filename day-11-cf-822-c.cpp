#include <iostream>
#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <algorithm>

struct trip
{
    int start;
    int end;
    int cost;

public:
    trip(int start, int end, int cost) : start(start), end(end), cost(cost) { }

    int get_duration()
    {
        return end - start + 1;
    }
};

int main()
{
    int num_trips, target_duration;

    std::cin >> num_trips >> target_duration;

    std::vector<trip> trips_by_start;
    std::vector<trip> trips_by_end;

    for(int i = 0; i < num_trips; i++) {
        int start, end, cost;

        scanf("%d %d %d", &start, &end, &cost);

        trips_by_start.push_back(trip(start, end, cost));
        trips_by_end.push_back(trip(start, end, cost));
    }

    std::sort(trips_by_start.begin(), trips_by_start.end(), [](trip& one, trip& another) {
        return one.start < another.start;
    });

    std::sort(trips_by_end.begin(), trips_by_end.end(), [](trip& one, trip& another) {
        return one.end < another.end;
    });

    /**
     * Stores minimum cost encountered of a trip of particular duration that ends up to the current point processed
     * in the loop
     */
    std::unordered_map<int, int> minimum_encountered_cost;

    int next_end = 0;

    int minimum_cost = INT32_MAX;

    for(int i = 0; i < num_trips; i++) {
        trip& current_trip = trips_by_start[i];

        /**
         * Update minimum costs among trips that end before this trip
         */
        while(next_end < num_trips && trips_by_end[next_end].end < current_trip.start) {
            trip& previous_trip = trips_by_end[next_end];

            if(minimum_encountered_cost.find(previous_trip.get_duration()) == minimum_encountered_cost.end()
               || previous_trip.cost < minimum_encountered_cost[previous_trip.get_duration()]) {
                minimum_encountered_cost[previous_trip.get_duration()] = previous_trip.cost;
            }

            next_end += 1;
        }

        int other_part = target_duration - current_trip.get_duration();

        if(minimum_encountered_cost.find(other_part) != minimum_encountered_cost.end()) {
            int candidate_cost = minimum_encountered_cost[other_part] + current_trip.cost;

            if(candidate_cost < minimum_cost) {
                minimum_cost = candidate_cost;
            }
        }
    }

    if(minimum_cost != INT32_MAX) {
        std::cout << minimum_cost << std::endl;
    }
    else {
        std::cout << -1 << std::endl;
    }
}
