#include <iostream>
#include <vector>

int main()
{
    int num_cars, alice_color;

    std::cin >> num_cars >> alice_color;

    std::vector<int> car_colors;

    for(int i = 0; i < num_cars; i++) {
        int color;

        std::cin >> color;

        car_colors.push_back(color);
    }

    
}
