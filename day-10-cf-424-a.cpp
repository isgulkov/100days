#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

int main()
{
    int num_people, num_keys, p;

    std::cin >> num_people >> num_keys >> p;

    std::vector<int> people;

    for(int i = 0; i < num_people; i++) {
        int person;

        std::cin >> person;

        people.push_back(person);
    }

    std::set<int> keys;

    for(int i = 0; i < num_keys; i++) {
        int key;

        std::cin >> key;

        keys.insert(key);
    }

    std::sort(people.begin(), people.end());

    std::vector<int> selected_keys;

    int max_distance = 0;

    for(int i = 0; i < num_people; i++) {
        int person = people[i];

        int person_distance = INT32_MAX;
        int selected_key;

        for(int key : keys) {
            int current_distance = abs(person - key) + abs(key - p);

            if(current_distance < person_distance) {
                person_distance = current_distance;
                selected_key = key;
            }
        }

        keys.erase(selected_key);
        selected_keys.push_back(selected_key);

        if(person_distance > max_distance) {
            max_distance = person_distance;
        }
    }

    std::sort(selected_keys.begin(), selected_keys.end());

    int real_max_distance = 0;

    for(int i = 0; i < num_people; i++) {
        int current_distance = abs(selected_keys[i] - people[i]) + abs(selected_keys[i] - p);

        if(current_distance > real_max_distance) {
            real_max_distance = current_distance;
        }
    }

    std::cout << real_max_distance << std::endl;
}
