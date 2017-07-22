#include <iostream>
#include <stdio.h>
#include <vector>
#include <tuple>
#include <map>

struct trip
{
    int id;
    int start;
    int end;
    int cost;

public:
    trip(int id, int start, int end, int cost) : id(id), start(start), end(end), cost(cost) { }

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

    int get_duration()
    {
        return end - start + 1;
    }
};

int main()
{
    int num_trips, target_duration;

    std::cin >> num_trips >> target_duration;

    std::vector<trip> trips;

    std::multimap<int, trip> trips_with_duration;

    for(int i = 0; i < num_trips; i++) {
        int start, end, cost;

        scanf("%d %d %d", &start, &end, &cost);

        trips.push_back(trip(i, start, end, cost));

        trips_with_duration.insert(std::make_pair(trips.back().get_duration(), trips.back()));
    }

    int minimum_cost = INT32_MAX;

    for(int i = 0; i < num_trips; i++) {
        trip& one_trip = trips[i];

        auto specific_duration_range = trips_with_duration.equal_range(target_duration - trips[i].get_duration());

        for(auto it = specific_duration_range.first; it != specific_duration_range.second; it++) {
            trip& another_trip = it->second;

            if(one_trip.id == another_trip.id) {
                continue;
            }

            if(one_trip.intersects_with(another_trip)) {
                continue;
            }

            int candidate_cost = one_trip.cost + another_trip.cost;

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
