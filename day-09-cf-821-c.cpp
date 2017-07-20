#include <iostream>
#include <stack>
#include <string>
#include <queue>

int main()
{
    int n;

    std::cin >> n;

    std::stack<int> stack;

    int num_reorderings = 0;
    int next_box_to_remove = 1;

    for(int i = 0; i < 2 * n; i++) {
        std::string command;

        std::cin >> command;

        if(command == "add") {
            int k;

            std::cin >> k;

            stack.push(k);
        }
        else if(command == "remove") {
            if(stack.top() != next_box_to_remove) {
                num_reorderings += 1;

                std::priority_queue<int> queue;

                int current_box;

                do {
                    current_box = stack.top();

                    stack.pop();

                    queue.push(current_box);
                } while(!stack.empty());

                while(!queue.empty()) {
                    stack.push(queue.top());

                    queue.pop();
                }
            }

            stack.pop();

            next_box_to_remove += 1;
        }
    }

    std::cout << num_reorderings << std::endl;
}
