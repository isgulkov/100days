#include <iostream>
#include <vector>

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

    
}
