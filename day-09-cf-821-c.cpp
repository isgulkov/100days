#include <iostream>
#include <vector>
#include <string>

int main()
{
    int n;

    std::cin >> n;

    std::vector<int> stack;

    for(int i = 0; i < 2 * n; i++) {
        std::string command;

        std::cin >> command;

        if(command == "add") {
            int k;

            std::cin >> k;

            stack.push_back(k);
        }
        else if(command == "remove") {
            stack.pop_back();
        }
    }

    std::cout << stack.size();
}
