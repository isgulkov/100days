#include <iostream>
#include <vector>
#include <set>

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
     * For every column, store starting indices of all sorted intervals on it
     */
    std::vector<std::set<int>> sorted_intervals((size_t)num_cols);

    for(int i = 0; i < num_cols; i++) {
        sorted_intervals[i].insert(0);

        for(int j = 1; j < num_rows; j++) {
            if(grid[j - 1][i] > grid[j][i]) {
                sorted_intervals[i].insert(j);
            }
        }
    }

    for(int i = 0; i < num_cols; i++) {
        for(int x : sorted_intervals[i]) {
            std::cout << x << " ";
        }

        std::cout << std::endl;
    }

}
