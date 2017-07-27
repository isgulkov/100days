#include <iostream>
#include <vector>

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

    for(person& person1 : people) {
        std::cout << person1.position << " " << person1.speed << " " << person1.direction << std::endl;
    }

    return 0;
}
