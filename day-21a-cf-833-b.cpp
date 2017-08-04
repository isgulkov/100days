#include <iostream>
#include <vector>

int main()
{
    int num_cakes, num_boxes;

    std::cin >> num_cakes >> num_boxes;

    std::vector<int> cakes((size_t)num_cakes);

    for(int i = 0; i < num_cakes; i++) {
        std::cin >> cakes[i];
    }
}
