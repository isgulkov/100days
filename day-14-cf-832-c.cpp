#include <iostream>
#include <vector>
#include <iomanip>

struct person
{
    int position;
    int speed;
    int direction;

    person(int position, int speed, int direction) : position(position), speed(speed)
    {
        if(direction == 1) {
            this->direction = -1;
        }
        else {
            this->direction = 1;
        }
    }
};

bool edges_reachable(std::vector<person>& people, int ray_speed, long double time)
{
    return false;
}

int main()
{
    int num_people, ray_speed;

    std::cin >> num_people >> ray_speed;

    std::vector<person> people;

    for(int i = 0; i < num_people; i++) {
        int x, v, t;

        std::cin >> x >> v >> t;

        people.push_back(person(x, v, t));
    }

    long double left = 0.0;
    long double right = 1000000.0;
    long double mid = 14.88;

    while(right - left > 0.0000001) {
        mid = left + (right - left) / 2.0;

        if(edges_reachable(people, ray_speed, mid)) {
            right = mid;
        }
        else {
            left = mid;
        }
    }

    std::cout << std::fixed << mid << std::endl;

    return 0;
}
