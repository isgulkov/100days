#include <iostream>
#include <vector>
#include <unordered_map>

int main()
{
    int num_cars, a_color;

    std::cin >> num_cars >> a_color;

    std::vector<int> car_colors;

    for(int i = 0; i < num_cars; i++) {
        int color;

        std::cin >> color;

        car_colors.push_back(color);
    }

    std::unordered_map<int, int> colors_to_counts;

    for(int color : car_colors) {
        if(color != a_color) {
            colors_to_counts[color] = 0;
        }
    }

    int a_color_count = 0;

    for(int i = 0; i < num_cars; i++) {
        int color = car_colors[i];

        if(color == a_color) {
            a_color_count += 1;

            for(auto it = colors_to_counts.begin(); it != colors_to_counts.end(); ) {
                /**
                 * Remove losing colors from the map
                 */

                if(it->second < a_color_count) {
                    it = colors_to_counts.erase(it);
                }
                else {
                    it++;
                }
            }
        }
        else if(colors_to_counts.find(color) != colors_to_counts.end()) {
            colors_to_counts[color] += 1;
        }
    }

    if(!colors_to_counts.empty()) {
        std::cout << colors_to_counts.begin()->first << std::endl;
    }
    else {
        std::cout << -1 << std::endl;
    }
}
