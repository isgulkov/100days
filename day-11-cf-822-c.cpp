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


}
