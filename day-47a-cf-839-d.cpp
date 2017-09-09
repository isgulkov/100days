#include <iostream>
#include <vector>

int main()
{
    int num_soldiers;

    std::cin >> num_soldiers;

    std::vector<int> strengths((size_t)num_soldiers);

    for(int i = 0; i < num_soldiers; i++) {
        std::cin >> strengths[i];
    }
}
