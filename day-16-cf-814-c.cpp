#include <iostream>
#include <string>
#include <vector>

class max_koyomity_calculator
{
    std::string initial_string;

    std::vector<std::vector<int>> max_koyomity;

    void precompute_max_koyomities(std::vector<int>& max_koyomities, char color)
    {
        for(int i = 0; i < max_koyomities.size(); i++) {
            max_koyomities[i] = 0;
        }
    }
public:
    max_koyomity_calculator(std::string initial_string) : initial_string(initial_string)
    {
        for(char color = 'a'; color <= 'z'; color++) {
            max_koyomity.push_back(std::vector<int>(initial_string.size() + 1));

            precompute_max_koyomities(max_koyomity.back(), color);
        }
    }

    int get_max_koyomity(int num_changes, char color)
    {
        return max_koyomity[color - 'a'][num_changes];
    }
};

int main()
{
    int string_length, num_requests;

    std::string initial_string;

    std::cin >> string_length >> initial_string >> num_requests;

    max_koyomity_calculator mkc(initial_string);

    for(int i = 0; i < num_requests; i++) {
        int num_changes;
        char fav_color;

        std::cin >> num_changes >> fav_color;

        std::cout << mkc.get_max_koyomity(num_changes, fav_color) << std::endl;
    }
}
