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

    bool people_sorted = false;

public:
    edge_reachability_checker(int ray_speed) : ray_speed(ray_speed) { }

    void add_person_facing_left(int position, int speed)
    {
        people_facing_left.push_back(person(position, speed));
    }

    void add_person_facing_right(int position, int speed)
    {
        people_facing_right.push_back(person(1000 * 1000 - position, speed));
    }

private:
    bool edge_reachable(person& p, long double time, int bomb_position) {
        /**
         * Determine if person p will reach position 0 in time `time`
         *
         * (assuming bomb_position >= p.position)
         */

        /**
         * Time that the person will travel at regular speed
         */
        long double t_regular = (bomb_position - p.position) / (long double)(ray_speed - p.speed);

        /**
         * Distance that the person will cover at regular speed
         */
        long double d_regular = t_regular * p.speed;

        /**
         * Total distance that the person will travel
         */
        long double d_total = d_regular + (p.speed + ray_speed) * (time - t_regular);

        return d_total >= p.position;
    };

    void populate_reachable(std::vector<person>& people, long double time, std::vector<bool>& reachable)
    {
        for(person& p : people) {
            if(p.position <= time * p.speed) {
                std::fill(reachable.begin(), reachable.end(), true);
                return;
            }
        }

        auto it_person = people.begin();

        for(int p_bomb = 0; p_bomb <= 1000 * 1000; p_bomb++) {
            reachable[p_bomb] = false;

            while(it_person != people.end() && it_person->position <= p_bomb) {
                if(edge_reachable(*it_person, time, p_bomb)) {
                    reachable[p_bomb] = true;
                    break;
                }
                else {
                    it_person++;
                }
            }
        }
    }

public:
    bool edges_reachable(long double time)
    {
        if(!people_sorted) {
            std::sort(people_facing_left.begin(), people_facing_left.end(), [](person& a, person&b) {
                return a.position < b.position;
            });

            std::sort(people_facing_right.begin(), people_facing_right.end(), [](person& a, person&b) {
                return a.position < b.position;
            });

            people_sorted = true;
        }

        std::vector<bool> left_edge_reachable(1000 * 1000 + 1);

        populate_reachable(people_facing_left, time, left_edge_reachable);

        std::vector<bool> right_edge_reachable(1000 * 1000 + 1);

        populate_reachable(people_facing_right, time, right_edge_reachable);

        for(int p_bomb = 0; p_bomb <= 1000 * 1000; p_bomb++) {
            if(left_edge_reachable[p_bomb] && right_edge_reachable[1000 * 1000 - p_bomb]) {
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

    std::cout << std::fixed << std::setprecision(20) << mid << std::endl;

    return 0;
}
