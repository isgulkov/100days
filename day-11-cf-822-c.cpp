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

struct trip_point
{
    int point;
    trip _trip;

    trip_point(int point, trip& _trip) : point(point), _trip(_trip) { }
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

    std::sort(trips.begin(), trips.end(), [](trip& one, trip& another) {
        return one.start < another.start;
    });

    std::vector<trip_point> trip_points;

    for(int i = 0; i < num_trips; i++) {
        trip& current_trip = trips[i];

        trip_points.push_back(trip_point(current_trip.start, current_trip));
        trip_points.push_back(trip_point(current_trip.end, current_trip));
    }

    std::sort(trip_points.begin(), trip_points.end(), [](trip_point& one, trip_point& another) {
       return one.point < another.point;
    });

    /**
     * Stores minimum cost encountered of a trip of particilar duration that ends up to the current point processed
     * in the loop
     */
    std::unordered_map<int, int> minimum_encountered_cost;

    int minimum_cost = INT32_MAX;

    for(int i = 0; i < 2 * num_trips; i++) {
        int current_point = trip_points[i].point;
        trip& current_trip = trip_points[i]._trip;

        if(current_point == current_trip.start) {
            int other_part = target_duration - current_trip.get_duration();

            if(minimum_encountered_cost.find(other_part) != minimum_encountered_cost.end()) {
                int candidate_cost = minimum_encountered_cost[other_part] + current_trip.cost;

                if(candidate_cost < minimum_cost) {
                    minimum_cost = candidate_cost;
                }
            }
        }

        if(current_point == current_trip.end) {
            if(minimum_encountered_cost.find(current_trip.get_duration()) == minimum_encountered_cost.end()
                    || current_trip.cost < minimum_encountered_cost[current_trip.get_duration()]) {
                minimum_encountered_cost[current_trip.get_duration()] = current_trip.cost;
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
