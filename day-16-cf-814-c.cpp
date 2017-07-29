#include <iostream>
#include <string>

int main()
{
    int string_length, num_requests;

    std::string initial_string;

    std::cin >> string_length >> initial_string >> num_requests;

    for(int i = 0; i < num_requests; i++) {
        int num_changes;
        char fav_color;

        std::cin >> num_changes >> fav_color;

        std::cout << num_changes << " " << fav_color << std::endl;
    }
}
