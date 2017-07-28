#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>

class edge_reachability_checker
{
    struct person
    {
        int position;
        int speed;

        person(int position, int speed) : position(position), speed(speed) { }
    };

    int ray_speed;

    std::vector<person> people_facing_left;
    std::vector<person> people_facing_right;

public:
    edge_reachability_checker(int ray_speed) : ray_speed(ray_speed) { }

    void add_person_facing_left(int position, int speed)
    {
        people_facing_left.push_back(person(position, speed));
    }

    void add_person_facing_right(int position, int speed)
    {
        people_facing_right.push_back(person(position, speed));
    }

private:
    enum boundary_type { START_LEFT, START_RIGHT, END_LEFT, END_RIGHT };

    struct boundary
    {
        int position;
        boundary_type type;

        boundary(int position, boundary_type type) : position(position), type(type) { }
    };

    std::pair<int, int> reachable_bomb_positions_left(person& p, long double time) {
        if(p.position <= p.speed * time) {
            return std::make_pair(0, 1000 * 1000);
        }
        else {
            return std::make_pair(p.position, (int)(ray_speed * time));
        }
    };

    std::pair<int, int> reachable_bomb_positions_right(person& p, long double time) {
        if(p.position + p.speed * time >= 1000 * 1000) {
            return std::make_pair(0, 1000 * 1000);
        }
        else {
            return std::make_pair((int)std::ceil(1000 * 1000 - ray_speed * time), p.position);
        }
    };

public:
    bool edges_reachable(long double time)
    {
        std::vector<boundary> boundaries;

        for(person& p : people_facing_left) {
            std::pair<int, int> segment = reachable_bomb_positions_left(p, time);

            if(segment.first <= segment.second) {
                boundaries.push_back(boundary(segment.first, START_LEFT));
                boundaries.push_back(boundary(segment.second, END_LEFT));
            }
        }

        for(person& p : people_facing_right) {
            std::pair<int, int> segment = reachable_bomb_positions_right(p, time);

            if(segment.first <= segment.second) {
                boundaries.push_back(boundary(segment.first, START_RIGHT));
                boundaries.push_back(boundary(segment.second, END_RIGHT));
            }
        }

        std::sort(boundaries.begin(), boundaries.end(), [](boundary& one, boundary& another) {
            if(one.position == another.position) {
                return one.type < another.type;
            }
            else {
                return one.position < another.position;
            }
        });

        // Scan for intersections
    }
};

int main()
{
    int num_people, ray_speed;

    std::cin >> num_people >> ray_speed;

    edge_reachability_checker ch(ray_speed);

    for(int i = 0; i < num_people; i++) {
        int position, speed, direction;

        std::cin >> position >> speed >> direction;

        if(direction == 1) {
            ch.add_person_facing_left(position, speed);
        }
        else {
            ch.add_person_facing_right(position, speed);
        }
    }

    long double left = 0.0;
    long double right = 1000 * 1000.0;
    long double mid = 14.88;

    while(right - left > 0.0000001) {
        mid = left + (right - left) / 2.0;

        if(ch.edges_reachable(mid)) {
            right = mid;
        }
        else {
            left = mid;
        }
    }

    std::cout << std::fixed << mid << std::endl;

    return 0;
}
