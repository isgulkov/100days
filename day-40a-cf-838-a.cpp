#include <iostream>
#include <vector>

class image
{
    std::vector<std::string> rows;

    int num_rows, num_cols;

public:
    image(int num_rows, int num_cols) : num_rows(num_rows), num_cols(num_cols) { }

    void add_row(std::string row)
    {
        rows.push_back(row);
    }
};

int main()
{
    int num_rows, num_cols;

    std::cin >> num_rows >> num_cols;

    image img(num_rows, num_cols);

    for(int i = 0; i < num_rows; i++) {
        std::string s;

        std::cin >> s;

        img.add_row(s);
    }
}
