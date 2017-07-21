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

    std::vector<int> keys;

    for(int i = 0; i < num_keys; i++) {
        int key;

        std::cin >> key;

        keys.push_back(key);
    }

    std::sort(people.begin(), people.end());

    int max_distance = 0;

    for(int i = 0; i < num_people; i++) {
        int person = people[i];

        std::sort(keys.begin(), keys.end(), [person](int one, int another) {
            return abs(one - person) < abs(another - person);
        });

        int person_distance = INT32_MAX;
        std::vector<int>::iterator selected_key;

        for(auto it = keys.begin(); it != keys.end(); it++) {
            int key = *it;

            int current_distance = abs(person - key) + abs(key - p);

            if(current_distance < person_distance) {
                person_distance = current_distance;
                selected_key = it;
            }
        }

        keys.erase(selected_key);

        if(person_distance > max_distance) {
            max_distance = person_distance;
        }
    }

    std::cout << max_distance << std::endl;
}
