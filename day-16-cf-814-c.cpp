#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class max_koyomity_calculator
{
    std::string initial_string;

    std::vector<std::vector<int>> max_koyomity;

    void precompute_max_koyomities(std::vector<int>& max_koyomities, char color)
    {
        std::fill(max_koyomities.begin(), max_koyomities.end(), 0);

        for(int r = 0; r < initial_string.size(); r++) {
            int num_changes = 0;

            for(int l = r; l >= 0; l--) {
                /**
                 * Check how many color changes are needed for this segment to become a consecutive segment of `color`
                 */

                if(initial_string[l] != color) {
                    num_changes += 1;
                }

                int score = r - l + 1;

                /**
                 * Update max koyomity for this number of color changes with current segment's length
                 */

                if(score > max_koyomities[num_changes]) {
                    max_koyomities[num_changes] = score;
                }
            }
        }

        /**
         * Max sure the max koyomity for each number of changes is not less than the koyomity for any of the smaller
         * numbers of changes, as not all provided changes need to be performed and a smaller but more advantageous
         * number of changes can be used instead
         */

        int max_koyomity = 0;

        for(int i = 0; i < max_koyomities.size(); i++) {
            if(max_koyomities[i] < max_koyomity) {
                max_koyomities[i] = max_koyomity;
            }
            else {
                max_koyomity = max_koyomities[i];
            }
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
