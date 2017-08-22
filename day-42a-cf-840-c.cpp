#include <iostream>
#include <vector>

int main()
{
    int num_items;

    std::vector<int> xs((size_t)num_items);

    for(int i = 0; i < num_items; i++) {
        std::cin >> xs[i];
    }
    
}
