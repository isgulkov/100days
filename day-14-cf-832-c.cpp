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
    bool left_edge_reachable(person& p, long double time, int bomb_position) {
        if(bomb_position < p.position) {
            return p.position - time * p.speed <= 0;
        }
        else {
            long double t_meet = (bomb_position - p.position) / (long double)(ray_speed - p.speed);
            long double x_meet = bomb_position - ray_speed * t_meet;

            return x_meet - (p.speed + ray_speed) * (time - t_meet) <= 0;
        }
    };

    bool right_edge_reachable(person& p, long double time, int bomb_position) {
        if(bomb_position > p.position) {
            return p.position + time * p.speed >= 1000 * 1000;
        }
        else {
            long double t_meet = (p.position - bomb_position) / (long double)(ray_speed - p.speed);
            long double x_meet = bomb_position + ray_speed * t_meet;

            return x_meet + (p.speed + ray_speed) * (time - t_meet) >= 1000 * 1000;
        }
    };

public:
    bool edges_reachable(long double time)
    {
        for(int p_bomb = 0; p_bomb <= 1000 * 1000; p_bomb++) {
            bool left_reachable = false;

            for(person& p : people_facing_left) {
                if(left_edge_reachable(p, time, p_bomb)) {
                    left_reachable = true;
                    break;
                }
            }

            if(!left_reachable) {
                continue;
            }

            for(person& p : people_facing_right) {
                if(right_edge_reachable(p, time, p_bomb)) {
                    return true;
                }
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
