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
            /**
             * Consider x a bomb position. Then time when ray meets the person:
             *
             * t_meet = (x - p.position) / (ray_speed - p.speed)
             *
             * Position where ray meets the person:
             *
             * x_meet = x - ray_speed * t_meet
             *
             * Position of the person after time `time` passed:
             *
             * x_final = x_meet - (ray_speed + p.speed) (time - t_meet)
             *
             * Solving x_final <= 0 for x yields right boundary for bomb position
             */
            long double right_boundary = p.speed * p.position / (long double)ray_speed
                                         + ray_speed * time - p.speed * p.speed * time / ray_speed;

            return std::make_pair(p.position, (int)right_boundary);
        }
    };

    std::pair<int, int> reachable_bomb_positions_right(person& p, long double time) {
        if(p.position + p.speed * time >= 1000 * 1000) {
            return std::make_pair(0, 1000 * 1000);
        }
        else {
            /**
             * Consider x a bomb position. Then time when ray meets the person:
             *
             * t_meet = (p.position - x) / (ray_speed - p.speed)
             *
             * Position where ray meets the person:
             *
             * x_meet = x + ray_speed * t_meet
             *
             * Position of the person after time `time` passed:
             *
             * x_final = x_meet + (ray_speed + p_speed) (time - t_meet)
             *
             * Solving x_final >= 10^6 for x yields right boundary for bomb position
             */
            long double left_boundary = 1000 * 1000 * (ray_speed - p.speed) / (long double)ray_speed
                                        + p.position * p.speed / (long double)ray_speed
                                        - ray_speed * time + p.speed * p.speed * time / ray_speed;

            return std::make_pair((int)std::ceil(left_boundary), p.position);
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

        int reach_left = 0, reach_right = 0;

        for(boundary& b : boundaries) {
            switch(b.type) {
                case START_LEFT:
                    reach_left += 1;
                    break;
                case START_RIGHT:
                    reach_right += 1;
                    break;
                case END_LEFT:
                    reach_left -= 1;
                    break;
                case END_RIGHT:
                    reach_right -= 1;
                    break;
            }

            if(reach_left && reach_right) {
                return true;
            }
        }

        return false;
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

    while(right - left > 0.0001 * 0.0001) {
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
