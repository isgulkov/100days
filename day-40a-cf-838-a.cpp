#include <iostream>
#include <vector>

class image
{
    std::vector<std::string> rows;

    std::vector<std::vector<int>> cumulative_ones;

    int num_rows, num_cols;

public:
    image(int num_cols) : num_rows(0), num_cols(num_cols) { }

    void add_row(std::string row)
    {
        rows.push_back(row);

        /**
         * For each pixel at position (i, j) maintain in `cumulative_ones[i][j]` how many ones total there are at this
         * position and anywhere to the left and to the top of it
         */
        cumulative_ones.push_back(std::vector<int>((size_t)num_cols, 0));

        for(int i = 0; i < num_cols; i++) {
            cumulative_ones[num_rows][i] = (row[i] == '1');

            if(num_rows > 0) {
                cumulative_ones[num_rows][i] += cumulative_ones[num_rows - 1][i];
            }

            if(i > 0) {
                cumulative_ones[num_rows][i] += cumulative_ones[num_rows][i - 1];
            }

            if(num_rows > 0 && i > 0) {
                cumulative_ones[num_rows][i] -= cumulative_ones[num_rows - 1][i - 1];
            }
        }

        num_rows += 1;
    }

    int ones_in_rect(int top, int left, int bottom, int right)
    {
        /**
         * Find the number of ones in the specified rectangle (borders inclusive)
         */

        /**
         * All pixels outside bottom and right borders of the image are considered "0"
         */
        if(bottom >= num_rows) {
            bottom = num_rows - 1;
        }

        if(right >= num_cols) {
            right = num_cols - 1;
        }

        int result = cumulative_ones[bottom][right];

        if(top > 0) {
            result -= cumulative_ones[top - 1][right];
        }

        if(left > 0) {
            result -= cumulative_ones[bottom][left - 1];
        }

        if(top > 0 && left > 0) {
            result += cumulative_ones[top - 1][left - 1];
        }

        return result;
    }
};

int main()
{
    int num_rows, num_cols;

    std::cin >> num_rows >> num_cols;

    image img(num_cols);

    for(int i = 0; i < num_rows; i++) {
        std::string s;

        std::cin >> s;

        img.add_row(s);
    }

    int best_k = -1;
    int best_result = INT32_MAX;

    for(int k = 2; k <= 2500; k++) {
        int current_result = 0;

        for(int i_row = 0; i_row < num_rows; i_row += k) {
            for(int i_col = 0; i_col < num_cols; i_col += k) {
                int ones = img.ones_in_rect(i_row, i_col, i_row + k - 1, i_col + k - 1);

                current_result += std::min(ones, k * k - ones);
            }
        }

        if(current_result < best_result) {
            best_result = current_result;
            best_k = k;
        }
    }

    std::cout << best_result << std::endl;
}
