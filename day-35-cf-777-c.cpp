#include <iostream>
#include <vector>

int main()
{
    int num_rows, num_cols;

    std::cin >> num_rows >> num_cols;

    std::vector<std::vector<int>> grid;

    for(int i = 0; i < num_rows; i++) {
        grid.push_back(std::vector<int>());

        for(int j = 0; j < num_cols; j++) {
            int cell;

            std::cin >> cell;

            grid.back().push_back(cell);
        }
    }

    /**
     * For each `l` store farthest_end[l] s.t. for any `r` <= farthest_end[l] there is a sorted interval [l; r] in some
     * of the columns
     */
    std::vector<int> farthest_end((size_t)num_rows, -1);

    for(int i = 0; i < num_cols; i++) {
        int begin = 0;

        for(int j = 1; j <= num_rows; j++) {
            if(j == num_rows || grid[j - 1][i] > grid[j][i]) {
                /**
                 * A sorted interval ends at index j - 1 at the current column
                 */

                int end = j - 1;

                for(int k = begin; k < j; k++) {
                    if(end > farthest_end[k]) {
                        farthest_end[k] = end;
                    }
                }

                begin = j;
            }
        }
    }

    int num_requests;

    std::cin >> num_requests;

    while(num_requests--) {
        int l, r;

        std::cin >> l >> r;

        if(farthest_end[l - 1] >= r - 1) {
            std::cout << "Yes" << std::endl;
        }
        else {
            std::cout << "No" << std::endl;
        }
    }
}
