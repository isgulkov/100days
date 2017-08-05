#include <iostream>
#include <vector>
#include <set>

int main()
{
    int num_cakes, num_boxes;

    std::cin >> num_cakes >> num_boxes;

    std::vector<int> cakes((size_t)num_cakes);

    for(int i = 0; i < num_cakes; i++) {
        std::cin >> cakes[i];
    }

    /**
     * Store maximum achievable score for subtasks with each number of cakes and k and k - 1 boxes
     */
    std::vector<std::vector<int>> max_score(2, std::vector<int>((size_t)num_cakes));

    std::set<int> cake_types;

    for(int i = 0; i < num_cakes; i++) {
        cake_types.insert(cakes[i]);

        max_score[0][i] = (int)cake_types.size();
    }

    for(int i_box = 1; i_box < num_boxes; i_box++) {
        for(int i_cake = 0; i_cake < num_cakes; i_cake++) {
            max_score[i_box % 2][i_cake] = 0;

            for(int box_start = 1; box_start < i_cake; box_start++) {
                int max_prev_score = max_score[(i_box - 1) % 2][box_start - 1];

                std::set<int> box_cakes;

                for(int i = box_start; i <= i_cake; i++) {
                    box_cakes.insert(cakes[i]);
                }

                int this_score = max_prev_score + (int)box_cakes.size();

                if(this_score > max_score[i_box % 2][i_cake]) {
                    max_score[i_box % 2][i_cake] = this_score;
                }
            }
        }
    }

    std::cout << max_score[(num_boxes - 1) % 2][num_cakes - 1] << std::endl;
}
