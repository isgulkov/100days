#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

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
            if(stack.back() != next_box_to_remove) {
                num_reorderings += 1;

                std::sort(stack.begin(), stack.end(), std::greater<int>());
            }

            stack.pop_back();

            next_box_to_remove += 1;
        }
    }

    std::cout << num_reorderings << std::endl;
}
