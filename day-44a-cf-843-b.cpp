#include <iostream>
#include <vector>
#include <chrono>

struct list_node
{
    int value;
    int next;
};

list_node send_ask_request(int index)
{
    std::cout << "? " << index << std::endl;

    int value, next;

    std::cin >> value >> next;

    return { value, next };
}

int main()
{
    int num_items, head, target;

    std::cin >> num_items >> head >> target;

    list_node current_lower_bound = send_ask_request(head);

    srand((unsigned int)time(nullptr));

    /**
     * Send 999 random requests to get a good chance of estabilishing a good lower bound (s.t. it is before the first
     * occurrence of `target` but by no more than 999 items)
     */

    for(int i = 0; i < 999; i++) {
        int random_index = 1 + (rand() + rand()) % num_items;

        list_node node = send_ask_request(random_index);

        if(node.value > current_lower_bound.value && node.value < target) {
            current_lower_bound = node;
        }
    }

    /**
     * Find the actual lower bound starting from our estimated lower bound
     */

    while(current_lower_bound.value < target && current_lower_bound.next != -1) {
        current_lower_bound = send_ask_request(current_lower_bound.next);
    }

    if(current_lower_bound.value >= target) {
        std::cout << "! " << current_lower_bound.value << std::endl;
    }
    else {
        std::cout << "! " << -1 << std::endl;
    }
}
