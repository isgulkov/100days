#include <iostream>
#include <stdio.h>
#include <vector>
#include <tuple>

struct trip
{
    int start;
    int end;
    int cost;

public:
    trip(int start, int end, int cost) : start(start), end(end), cost(cost) { }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCSimplifyInspection"
    bool intersects_with(trip& other)
    {
        if(start < other.start && end >= other.start) {
            /**
             * Case 1:
             *
             * [-----------] one
             *     [-------------] other
             *
             * [------------------------------] one
             *     [-------------] other
             */
            return true;
        }
        else if(other.start < start && other.end >= start) {
            /**
             * Case 2:
             *
             *       [-----------] one
             * [-------------] other
             *
             * [------------------------------] one
             * [-------------] other
             */
            return true;
        }
        else {
            return false;
        }
    }
#pragma clang diagnostic pop
};

int main()
{
    int num_trips, target_duration;

    std::cin >> num_trips >> target_duration;

    std::vector<trip> trips;

    for(int i = 0; i < num_trips; i++) {
        int start, end, cost;

        scanf("%d %d %d", &start, &end, &cost);

        trips.push_back(trip(start, end, cost));
    }

    int minimum_cost = INT32_MAX;

    for(int i = 0; i < num_trips; i++) {
        for(int j = 0; j < num_trips; j++) {
            if(i == j) {
                continue;
            }

            if(trips[i].intersects_with(trips[j])) {
                continue;
            }

            int candidate_cost = trips[i].cost + trips[j].cost;

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
