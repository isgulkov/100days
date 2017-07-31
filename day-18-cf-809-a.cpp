#include <iostream>
#include <vector>

int main()
{
    int num_computers;

    std::cin >> num_computers;

    std::vector<int> positions((size_t)num_computers);

    for(int i = 0; i < num_computers; i++)
    {
        std::cin >> positions[i];
    }

    std::sort(positions.begin(), positions.end());

    for(auto p : positions) {
        std::cout << p << " ";
    }

    std::cout << std::endl;
}
