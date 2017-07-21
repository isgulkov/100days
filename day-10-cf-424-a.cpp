#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

int main()
{
    int num_people, num_keys, office_pos;

    std::cin >> num_people >> num_keys >> office_pos;

    std::vector<int> people;

    for(int i = 0; i < num_people; i++) {
        int person;

        std::cin >> person;

        people.push_back(person);
    }

    std::vector<int> keys;

    for(int i = 0; i < num_keys; i++) {
        int key;

        std::cin >> key;

        keys.push_back(key);
    }

    std::sort(people.begin(), people.end());
    std::sort(keys.begin(), keys.end());

    int smallest_max_distance = INT32_MAX;

    for(int keys_offset = 0; keys_offset < num_keys - num_people; keys_offset++) {
        int current_max_distance = 0;

        for(int i = 0; i < num_people; i++) {
            int current_distance = abs(people[i] - keys[keys_offset + i]) + abs(keys[keys_offset + i] - office_pos);

            if(current_distance > current_max_distance) {
                current_max_distance = current_distance;
            }
        }

        if(current_max_distance < smallest_max_distance) {
            smallest_max_distance = current_max_distance;
        }
    }

    std::cout << smallest_max_distance << std::endl;
}
