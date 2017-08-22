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
}
