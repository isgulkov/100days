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

    for(int i = 0; i < num_rows; i++) {
        for(int j = 0; j < num_cols; j++) {
            std::cout << grid[i][j] << " ";
        }

        std::cout << std::endl;
    }

}
