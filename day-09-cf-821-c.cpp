#include <iostream>
#include <vector>
#include <string>

int main()
{
    int n;

    std::cin >> n;

    std::vector<int> stack;

    int num_reorderings = 0;
    int next_box_to_remove = 1;

    for(int i = 0; i < 2 * n; i++) {
        std::string command;

        std::cin >> command;

        if(command == "add") {
            int k;

            std::cin >> k;

            stack.push_back(k);
        }
        else if(command == "remove") {
            if(!stack.empty()) {
                if(stack.back() != next_box_to_remove) {
                    num_reorderings += 1;

                    /**
                     * Clear the stack and assume that all the elements on it are there and in sorted order
                     */
                    stack.clear();
                }
                else {
                    stack.pop_back();
                };
            }

            /**
             * Consider removal requests on empty stack be fulfilled because:
             * * by formulation the requested elements will be on the stack;
             * * by the assumption that we have sorted the stack they will be at the top
             */

            next_box_to_remove += 1;
        }
    }

    std::cout << num_reorderings << std::endl;
}
